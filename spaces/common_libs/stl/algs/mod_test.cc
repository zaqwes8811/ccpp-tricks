// Notes:
//   с ассоциативными как-то все на так в плане алгоритмов
#include "visuality/view.h"

#include <gtest/gtest.h>

#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <list>
#include <deque>
#include <valarray>
#include <numeric>

using namespace std;
using namespace view;
/// Modif. algs
// - in work time
// - on copy

namespace {
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

/// No modif. algs
// p. 334
TEST(STL, ForEach) {
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
  // Похоже сам объект это первый аргумента, а что передает методу - второй итого 2а
  for_each(persons.begin(), persons.end(), bind2nd/*bind1st*/(mem_fun_ref(&Person::printTagged), string("person :")));

  // If args > 2
  // http://stackoverflow.com/questions/10692121/c-bind-function-for-use-as-argument-of-other-function
  // C++03 - Boost
  // C++11 - stl


  vector<Person*> persons_ptrs;  // diff. for ptrs
  persons_ptrs.push_back(new Person);
  //for_each(persons_ptrs.begin(), persons_ptrs.end(), mem_fun(&Person::print));
}

TEST(STL, Copy) {
  // copy - похоже нельзя копировать в себя
  //TODO: как скопировать по критерию
  using std::copy;
  using std::back_inserter;

  vector<int> coll1;
  list<int> coll2;
  insert_elems(coll1, 1, 9);

  copy(coll1.begin(), coll1.end(),
       back_inserter(coll2));
  assert(coll1.size() == coll2.size());

  // DANGER:
  // p. 278
  // Если передать итераторы, а затем вставить элементы, и при этом
  //   контейнер перераспределит память, операция испортит итераторы
  // Eff. stl - http://cpp.com.ru/meyers/ch2.html#t29

  // size(), capacity()
  // "Речь идет об общемколичестве элементов, а не о том,
  //   сколько еще элементов можно разместить без расширения контейнера."
  coll1.reserve(2*coll1.size());
  copy(coll1.begin(), coll1.end(),
       back_inserter(coll1));

  //TODO: copy by mask
}

//Del
// для списков есть более эффективные функции
TEST(STL, Remove) {
  using std::less;

  vector<int> coll;
  insert_elems(coll, 2, 6);
  insert_elems(coll, 4, 9);
  insert_elems(coll, 1, 7);
  print_elems(coll, "coll: ");

  vector<int>::iterator pos;
  pos = remove(coll.begin(), coll.end(),
               5);
  print_elems(coll, "size not changed: ");
  coll.erase(pos, coll.end());
  print_elems(coll, "size changed: ");

  coll.erase(remove_if(coll.begin(), coll.end(),
                       bind2nd(less<int>(), 4)),
             coll.end());
  print_elems(coll, "removed < 4: ");
}

}  // namespace

