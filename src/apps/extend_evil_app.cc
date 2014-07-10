#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

#include <typeinfo>  // не хотелось бы включать, но похоже нужно

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using std::ostream;
using std::string;
using std::endl;
using std::cout;
using std::vector;

// C++11
using std::move;

namespace ps_sample_shared_extend {
// Если большие объекты, но почему так работает? Почему не копий?
template<typename T>
void draw(const T& x, ostream& out, size_t position)  // object_t -> int and move here
{ out << string(position, ' ') << x << endl; }

class object_t {
public:
  template<typename T>
  // make_ptr
  object_t(const T& x) : self_(boost::make_shared<model<T>>(move(x))) {}

  friend void draw(const object_t &x, ostream &out, size_t position)
  { x.self_->draw_(out, position); }

private:
  struct concept_t {
    virtual ~concept_t() = default;
    virtual void draw_(ostream& out, size_t position) const = 0;
  };

  template<typename T>
  struct model : concept_t {
    model(const T& x) : data_(move(x)) { }
    void draw_(ostream& out, size_t position) const
    { draw(data_, out, position); }
    T data_;
  };

  // std::unique_ptr<int_model_t> self_;
  //std::
  boost::shared_ptr<const concept_t> self_;  // ссылки на immutable
};

using document_t = vector<object_t>;  // полиморфизм только через shared_ptrs

void draw(const document_t&x, ostream &out, size_t position)
{
  out << string(position, ' ') << "<document>" << endl;
  for (const auto& e : x) draw(e, out, position + 2);
  out << string(position, ' ') << "</document>" << endl;
}

/// Ps
using history_t = vector<document_t>;
void commit(history_t& x) {
  assert(x.size());
  x.push_back(x.back());
}

void undo(history_t& x) { assert(x.size()); x.pop_back(); }

document_t& current(history_t& x) {
  assert(x.size());
  return x.back();
}
}

namespace external_space  {
// не нужно ничего наследовать.
class my_class_t {
public:
  my_class_t() {}
  my_class_t(const my_class_t&) { cout << "copy my_class\n"; }
};

void draw(const my_class_t&, ostream& out, size_t position)
{ out << string(position, ' ') << "my_class_t()" << endl; }
}

TEST(EvelPsExtend, App) {
  using namespace ps_sample_shared_extend;
  using namespace external_space;
  history_t h(1);

  // Работаем с верхним элементом
  //current(h).emplace_back(0);
  //current(h).emplace_back(string("Hello!"));
  current(h).emplace_back(my_class_t());

  draw(current(h), cout, 0);
  cout << "-------------" << endl;

  commit(h);  // сохраняем текущую и ее копируем на верх.
  cout << "-------------" << endl;

  //current(h).emplace_back(current(h));
  current(h).emplace_back(my_class_t());
  current(h)[4] = my_class_t();

  draw(current(h), cout, 0);
  cout << "-------------" << endl;

  undo(h);
  draw(current(h), cout, 0);

}

// TODO: add features to class
