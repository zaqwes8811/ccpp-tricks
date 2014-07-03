// http://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

#include <gtest/gtest.h>

using std::ostream;
using std::string;
using std::endl;
using std::cout;
using std::vector;

//using object_t = int;  // step 2

void draw(const int& x, ostream& out, size_t position)  // object_t -> int and move here
{ out << string(position, ' ') << x << endl; }

/*
// step 3: remove
class object_t {
public:
  object_t(const int& x) : self_(x)
  {}

  friend void draw(const object_t &x, ostream &out, size_t position)
  { draw(x.self_, out, position); }

private:
  int self_;
};*/

class object_t {
public:
  object_t(const int& x) : self_(new int_model_t(x))
  { }

  object_t(const object_t& x) : self_(new int_model_t(*x.self_))
  { }  // если оставить только копирующий констр. компилятор (gcc 4.7) заругается

  object_t& operator=(const object_t& x)
  { object_t tmp(x);
    self_ = std::move(tmp.self_);
    //std::swap(self_, tmp.self_);  // also compiled, but may be not exc. safe
    return *this; }

  friend void draw(const object_t &x, ostream &out, size_t position)
  { x.self_->draw_(out, position); }  // разрешаем доступ к закрытым частям

private:
  struct int_model_t {
    int_model_t(const int& x) : data_(x) { }
    void draw_(ostream& out, size_t position) const
    {draw(data_, out, position);}

    int data_;
  };
  std::unique_ptr<int_model_t> self_;
};

using document_t = vector<object_t>;  // полиморфизм только через shared_ptrs

void draw(const document_t&x, ostream &out, size_t position)
{
  out << string(position, ' ') << "<document>" << endl;
  for (const auto& e : x) draw(e, out, position + 2);
  out << string(position, ' ') << "</document>" << endl;
}

TEST(EvelC11, App) {
  // TODO:
  document_t document;

  document.emplace_back(0);
  document.emplace_back(1);
  document.emplace_back(2);
  document.emplace_back(3);

  std::reverse(document.begin(), document.end());

  draw(document, cout, 0);
}
