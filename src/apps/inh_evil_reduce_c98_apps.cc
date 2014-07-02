// http://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil
// TODO: C++98
#include <string>
#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include <boost/foreach.hpp>

#define foreach_         BOOST_FOREACH

//using object_t = int;  // C++11
using std::ostream;
using std::endl;
using std::string;
using std::vector;
using std::cout;

typedef int object_t;
typedef vector<object_t> document_t;

void draw(const object_t& x, ostream& out, size_t position)
{ out << string(position, ' ') << x << endl; }

void draw(const document_t& x, ostream& out, size_t position)
{
  out << string(position, ' ') << "<document>" << endl;
  // for (const auto& e : x) draw(e, out, position + 2); // C++11
  // C++98 without explicit loop and boost imposible. 2 arg max
  //
  // std::for_each не выходит замкнуть сторонние параметры
  // можно создать объект, но как быть с сохранением ostream& it's link!!
  //
  // http://www.boost.org/doc/libs/1_55_0/doc/html/foreach.html
  foreach_(const object_t& e, x) draw(e, out, position);

  out << string(position, ' ') << "</document>" << endl;
}


TEST(Evil, App) {
  document_t doc;
  doc.push_back(2);

  draw(doc, cout, 0);
}
