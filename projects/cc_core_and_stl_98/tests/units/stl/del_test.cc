// Notes:
//   с ассоциативными как-то все на так в плане алгоритмов
#include "visuality/view.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <string>
#include <valarray>
#include <vector>

using namespace std;
using namespace view;
/// Modif. algs
// - in work time
// - on copy

//Del
// для списков есть более эффективные функции
// те что с copy похоже не меняют входного интервала
TEST(STL, Remove_fun) {
  // http://www.gotw.ca/gotw/051.htm

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
  
  // своя erase уже знает что делать с элементами, на вход идут итератор
  vector<int>::iterator next = coll.erase(pos, coll.end());  // Возвращает VALIDE(!!!) итератор
  // с ассоциативными не все так просто.

  print_elems(coll, "size changed: ");

  coll.erase(remove_if(
      coll.begin(), coll.end(),
                      bind2nd(less<int>(), 
                      4)),
             coll.end());
  print_elems(coll, "removed < 4: ");

  // удаления с копированием
  // http://stackoverflow.com/questions/11928115/why-doesnt-stdremove-copy-if-actually-remove
  coll.clear();
  insert_elems(coll, 1, 7);
  vector<int> c_save = coll;
  cout << coll;
  vector<int> e;
  remove_copy_if(coll.begin(), coll.end(), back_inserter(e), bind2nd(less<int>(), 4));
  cout << e << coll;
  assert(coll == c_save);

  //
  // FIXME: из-за особенностей remove возникает проблема с удалением 
  //   указателей на динамическую память, или не управл. хендлов.
  // v0 - partion
  // v1 - delete, set null, del null - конт. не должен сод. null-elems
  //   !!! static_cast<Widget*>(0) !!! не просто 0

  // copy_if
  // remove_copy_if(begin,end,destBegin,not1(p));  // !BAD impl
}

TEST(stl, unique_fun) {
  // удаляем одинаковые соседние, либо условно копирует

}
