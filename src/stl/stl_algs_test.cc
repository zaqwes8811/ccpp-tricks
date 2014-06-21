
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <list>
#include <deque>

#include <gtest/gtest.h>

using std::for_each;
using std::transform;
using std::vector;
using std::copy;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::list;

using std::bind2nd;
using std::bind1st;
using std::mem_fun_ref;
using std::mem_fun;
using std::string;
using std::search_n;
using std::greater;
using std::distance;
using std::deque;


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

TEST(STL, Find) {
  // . . . [4 ... 4] . . .
  list<int> coll;
  insert_elems(coll, 1, 9);
  insert_elems(coll, 1, 9);

  list<int>::iterator pos1, pos2;
  pos1 = find(coll.begin(), coll.end(), 4);  // find first
  if (pos1 != coll.end())
    pos2 = find(++pos1, coll.end(), 4); // нач. со след. за найденным

  // print
  if (pos1 != coll.end() && pos2 != coll.end())
    copy(--pos1, ++pos2, ostream_iterator<int>(cout, " "));
  cout << endl;
}

TEST(STL, SearchNBySomeCriteria) {
  // поиск 4 послед. больших 3
  vector<int> coll;
  insert_elems(coll, 1, 9);
  print_elems(coll);

  vector<int>::iterator pos;
  pos = search_n(coll.begin(), coll.end(),  // interval
                 4, // counter
                 3);  // value
  assert(pos == coll.end());

  // no search_n_if version
  pos = search_n(coll.begin(), coll.end(),
                 4,
                 3, greater<int>());  // no STL way. Причем предикат бинарный

  assert(distance(coll.begin(), pos)+1 == 4);
}

TEST(STL, SearchSubInterval) {
  deque<int> coll;
  list<int> subcoll;
  insert_elems(coll, 1, 7);
  insert_elems(coll, 1, 7);

  insert_elems(subcoll, 3, 6);

  // finding
  deque<int>::iterator pos;
  pos = search(coll.begin(), coll.end(),
               subcoll.begin(), subcoll.end());

  while(pos != coll.end()) {
      // next
      ++pos;
      pos = search(pos, coll.end(),
                   subcoll.begin(), subcoll.end());
  }

  // search any from interval forward and back
  pos = find_first_of(coll.begin(), coll.end(),
                      subcoll.begin(),
                      subcoll.end());
  assert(*pos == 3);

  // need
  // TODO: как это сработало?
  deque<int>::reverse_iterator rpos;
  rpos = find_first_of(coll.rbegin(), coll.rend(),
                      subcoll.begin(),
                      subcoll.end());
  assert(*rpos == 6);
}

// p. 346
TEST(STL, SearchWithPred) {

}

// p. 351
bool doubled(int elem, int nextElem) {
  return elem * 2 == nextElem;
}

TEST(STL, FindAdja) {
  using std::adjacent_find;

  vector<int> coll;
  coll.push_back(1);
  coll.push_back(3);
  coll.push_back(2);
  coll.push_back(4);
  coll.push_back(5);
  coll.push_back(5);
  coll.push_back(0);

  vector<int>::iterator pos;
  pos = adjacent_find(coll.begin(), coll.end());
  assert(*pos == 5);

  pos = adjacent_find(coll.begin(), coll.end(),
                      doubled);
  assert(*pos == 2);
}

// summary:
// p. 303 - не должен изменять состояние

class Nth {
private:
  int nth;
  int count;
public:
  Nth(int n) : nth(n), count(0) {}
  bool operator() (int) /* must be const, but accamulate? */ {
    return ++count == nth;
  }
};

TEST(STL, WrongPredicate) {
  using std::remove_if;

  list<int> coll;
  insert_elems(coll, 1, 9);
  print_elems(coll);

  // del 3
  list<int>::iterator pos;
  pos = remove_if(coll.begin(), coll.end(),
                  Nth(3));

  coll.erase(pos, coll.end());
  print_elems(coll, "nth removed: ");  // !! удален и 6 тоже!!
}

/// Modif. algs

