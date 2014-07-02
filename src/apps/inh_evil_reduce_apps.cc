// http://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil
// TODO: C++98
#include <string>
#include <iostream>
#include <vector>

#include <gtest/gtest.h>

//using object_t = int;  // C++11
using std::ostream;
using std::endl;
using std::string;
using std::vector;

typedef int object_t;
typedef vector<object_t> document_t;
void draw(const object_t& x, ostream& out, size_t position)
{ out << string(position, ' ') << x << endl; }

void draw(const document_t& x, ostream& out, size_t position)
{
  out << string(position, ' ') << "<document>" << endl;
  // for (const auto& e : x) draw(e, out, position + 2); // C++11
  out << string(position, ' ') << "</document>" << endl;
}


TEST(Evil, App) {

}
