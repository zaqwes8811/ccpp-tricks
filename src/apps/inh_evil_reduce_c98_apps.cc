// http://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil
// TODO: C++98
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

#include <gtest/gtest.h>
#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>

#define foreach_         BOOST_FOREACH

//using object_t = int;  // C++11
using std::ostream;
using std::endl;
using std::string;
using std::vector;
using std::cout;

//typedef int object_t;

// Con: If no-C++11 много копирований.
//
// Pro: value-sem.
template<typename T>
void draw(const T& x, ostream& out, size_t position)  // object_t -> int and move here
{
  out << string(position, ' ');
  out << x;
  out << endl;
}

//template<typename T>  // не тут
class object_t {
public:
  // шаблонный конструктор
  // http://ldmitrieva.blogspot.ru/2010/11/blog-post_12.html
  template<typename T>
  object_t(T x) : self_(new model<T>(/*move*/(x)))  // by value/ специализируем шаблонный класс
  {cout << "ctor\n";}

  object_t(const object_t& x) : self_(x.self_->copy_())
  { cout << "copy\n";}  // если оставить только копирующий констр. компилятор (gcc 4.7) заругается

  object_t& operator=(const object_t& x)
  {
    object_t tmp(x);
    //std::swap(self_, tmp.self_);  // also compiled, but may be not exc. safe
    self_.swap(tmp.self_);
    return *this;
  }

  //void swap()

  friend void draw(const object_t &x, ostream &out, size_t position)
  {
    x.self_->draw_(out, position);
  }  // разрешаем доступ к закрытым частям

private:
  struct concept_t {
    virtual ~concept_t() {} //= default;
    virtual concept_t* copy_() const = 0;
    virtual void draw_(ostream& out, size_t position) const = 0;
  };

  // Шаблонный класс и обычный конструктор.
  template<typename T>
  struct model : concept_t {
    model(const T& x) : data_(/*move*/(x)) { }
    void draw_(ostream& out, size_t position) const
    {
      // !!Most important - it's terminal function
      draw(data_, out, position);
    }

    concept_t* copy_() const { return new model(*this); }

    T data_;
  };

  /// Handle
  //std::unique_ptr<concept_t> self_;
  //
  //concept_t* self_;
  //
  // http://www.rsdn.ru/forum/cpp/1698137.all
  //std::auto_ptr<concept_t> self_;
  //
  boost::scoped_ptr<concept_t> self_;
};

//using document_t = vector<object_t>;  // полиморфизм только через shared_ptrs
typedef vector<object_t> document_t;

void draw(const document_t&x, ostream &out, size_t position)
{
  out << string(position, ' ') << "<document>" << endl;
  for (document_t::const_iterator e = x.begin(), end = x.end(); e != end; ++e) {
    draw(*e, out, position + 2);
  }
  out << string(position, ' ') << "</document>" << endl;
}

// не нужно ничего наследовать.
class my_class_t {

};

void draw(const my_class_t&, ostream& out, size_t position)
{ out << string(position, ' ') << "my_class_t()" << endl; }

TEST(EvelC11, App) {
  // TODO:
  document_t document;
  document.reserve(5);

  // И при занесении копируется
  document.push_back(0);
  document.push_back(string("hello"));
  document.push_back(2);
  document.push_back(my_class_t());

  std::reverse(document.begin(), document.end());

  draw(document, cout, 0);

  object_t a(document);
  object_t b(my_class_t());
  //std::swap(a, b);
  //a = b;  // TODO: not compiled if diff. types, but how work containers?!
  //b = a;
  // http://en.cppreference.com/w/cpp/language/typeid
  // RTII cost:
  // http://stackoverflow.com/questions/579887/how-expensive-is-rtti
  assert(typeid(document[0]) == typeid(document[1]));
}


TEST(Evil, App) {
  document_t doc;
  doc.push_back(2);

  draw(doc, cout, 0);
}
