
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <string>

#include <gtest/gtest.h>

using std::for_each;
using std::transform;
using std::vector;
using std::copy;
using std::cout;
using std::endl;
using std::ostream_iterator;

using std::bind2nd;
using std::bind1st;
using std::mem_fun_ref;
using std::mem_fun;
using std::string;


template<class T>
inline void print_elems(const T& coll, const char* optcstr="") {
  typename T::const_iterator pos;
  cout << optcstr;
  for (pos = coll.begin(); pos != coll.end(); ++pos)
    cout << *pos << ' ';
  cout << endl;
}

template<class T>
inline void insert_elems(T& coll, int first, int last) {
  for (int i = first; i <= last; ++i)
    coll.insert(coll.end(), i);
}

void square(int& elem) {
  elem = elem * elem;
}

int square_tr(int& elem) {  // для transform кажется можно и по ссылке и по значению
  elem = elem * elem;
  return elem;
}

TEST(STL, Base) {
  // p. 325
  // часто задается начало конец первого и начало второго, поэтому нужно чтобы хватало
  // ? в основном работают в режиме замены, а не вставки
  //
  // вместо for_each лучше использовать подх. для конкр. задачи

  /// Modif.: main - for_each and transform
  vector<int> coll;
  coll.push_back(9);

  // http://stackoverflow.com/questions/3185132/how-to-combine-a-function-and-a-predicate-in-for-each
  for_each(coll.begin(), coll.end(), square);
  copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, "\n"));
  transform(coll.begin(), coll.end(), coll.begin(), square_tr);
  copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, "\n"));

  // приемниками модиф. не могут быть ассоц. контейнеры?

  /// Перестановочные
}

void print(int elem) {
  cout << elem << ' ';
}

class Person {
private:
  string name;
public:
  Person() : name("one") {}
  void print() const {
    cout << name << endl;
  }

  void printTagged(const string& tag) const {
    cout << tag << name << endl;
    //print();
  }
};
// p. 334
TEST(STL, Concretic) {
  /// for_each
  //TODO: можно вызывать метод класса, как-то через mem_fun - p. 307
  vector<int> coll;
  insert_elems(coll, 1, 9);
  for_each(coll.begin(), coll.end(), print);
  cout << endl;
  vector<Person> persons(5);
  //for_each(persons.begin(), persons.end(), mem_fun_ref(&Person::print));

  // Troubles
  // http://stackoverflow.com/questions/1464439/using-stdbind2nd-with-references
  // if "string" not string("string") - method get "" - gcc 4.7.2
  for_each(persons.begin(), persons.end(), bind2nd/*bind1st*/(mem_fun_ref(&Person::printTagged), string("person :")));


  vector<Person*> persons_ptrs;  // diff. for ptrs
  persons_ptrs.push_back(new Person);
  //for_each(persons_ptrs.begin(), persons_ptrs.end(), mem_fun(&Person::print));
}
