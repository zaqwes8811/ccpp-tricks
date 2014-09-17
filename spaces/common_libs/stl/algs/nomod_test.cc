// Notes:
//   с ассоциативными как-то все на так в плане алгоритмов

#include "visuality/view.h"

#include <gtest/gtest.h>
//#include <

#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <list>
#include <deque>
#include <valarray>
#include <numeric>

namespace {

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

using namespace view;
using namespace std;

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

// [value, bound)
struct pred_upper_bound {
  explicit pred_upper_bound(int b) : boundary(b) {}
  int boundary;
  bool operator()(const int value) const {
    return value < boundary;
  }
};

TEST(STL, AllInOne) {
  //
  vector<int> v;
  insert_elems(v, 1, 9);
  insert_elems(v, 1, 9);
  cout << v;

  // считаем по (==) - equal for objects
  assert(2 == count(v.begin(), v.end(), 9));
  assert(4 == count_if(v.begin(), v.end(), pred_upper_bound(3)));

  assert(v.end() == find(v.begin(), v.end(), 89));

  // преобразуем бинарный в унарный
  assert(v.end() 
    != find_if(v.begin(), v.end(), bind2nd(greater<int>(), 7))
  );

  // поиск подряд идущих
  std::vector<int>::iterator it = search_n(v.begin(), v.end(), 2, 7);
  assert(it == v.end());  // нет заданного числа повторений

  // вставка перед элеметом на который указывает - отодвигает элемент, на кот. указывает
  v.insert(v.begin()+7, 7);  // не действительными могут стать итер. как все после, так и вообще
  v.insert(v.end(), 17);  // перед end!
  cout << v;

  assert(v.end() == search_n(
      v.begin(), v.end(), 
      4, 
      9, 
      greater<int>()));  // можно без связывания

  vector<int> pattern;
  insert_elems(pattern, 1, 2);

  // FIXME: а если интервал, который ищем больше исходного? да кажется все равно
  /// поиск паттерна
  {
    // from begin
    int count = 0;
    vector<int>::iterator start = v.begin();
    while (true) {
      it = search(
          start, v.end(), 
          pattern.begin(), pattern.end());

      if (it == v.end()) 
        break;

      // next step
      start = it;
      advance(start, pattern.size());  

      // processing
      cout << vector<int>(it, start);  // интервал валдный, т.к. раз нашли, значит все норм
      ++count;
    }
    assert(count == 2);

    // from end
  }

  // 
  vector<int>::iterator stop = v.end();
  while (true) {
    it = find_end(
          v.begin(), stop, 
          pattern.begin(), pattern.end());

    if (it == stop)  // not v.end()
      break;

    stop = it;// - pattern.size();

    advance(it, pattern.size());
    cout << vector<int>(stop, it);  // интервал валдный, т.к. раз нашли, значит все норм
  }

  // поиск вероятных
}

//equal_to<string::value_type>()  // удаляет все
//bind2nd(equal_to<char>(), ' ');  // нужен был бинарный предикат
struct spaces_purger
{
  bool operator()(string::value_type f, string::value_type n) const {
    return isspace(f) && isspace(n);
  }
};


// distance(s.begin()+offset, s.end())) 
// substr не катит - возвращает копию
// http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

/*
{
  //Idx offset = 0;
  Idx end_it = string::npos;

  while (true) {
    Idx endpos = s.rfind(" ");

    if (endpos != end_it) 
      break;

    string tmp(s.begin() + (endpos + 1), end_it);
    tmp.append(" ");

    // найденный итерато не действителен
    cout << s << "<" << endl;
    break;
  }

  //s.insert(s.begin(), tmp.begin(), tmp.end());
  //s.erase(s.begin() + endpos + tmp.size(), s.end());
}
*/
//typedef string::size_type Idx;
// http://stackoverflow.com/questions/1011790/why-does-stdstring-findtext-stdstringnpos-not-return-npos
TEST(OJ, Reverse) {
  string s("  the   skyy is  blue   ");
  s = "a";
  s = "   ";
  
  // убираем повторяющиеся пробелы
  s.erase(
      unique(s.begin(), s.end(), spaces_purger()), 
      s.end());

  if (s == " ") s = "";
  
  {
    // trim - no copy
    string::size_type endpos = s.find_last_not_of(" ");  // size_t нельзя!!!
    // раз не равно, то можно еще прибавить
    if (string::npos != endpos) s.erase(s.begin()+endpos+1, s.end()); 

    string::size_type startpos = s.find_first_not_of(" ");
    if( string::npos != startpos ) s.erase(s.begin(), s.begin()+startpos);
  }

  // Real work
  // нарезать слишком долго
  // чтобы не искать с конца вращаем всю строку
  reverse(s.begin(), s.end());
  
  {
    // вращает отдельные слова
    string::size_type offset = 0;
    while (true) {
      string::size_type space_pos = s.find(" ", offset);  
      if (space_pos == string::npos) {
        reverse(s.begin()+offset, s.end());  // последнюю не найдет
        break;
      }
      reverse(s.begin()+offset, s.begin()+space_pos);
      offset = space_pos+1;
    }
  }
}
}  // namespace
