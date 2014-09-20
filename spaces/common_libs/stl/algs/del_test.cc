// Notes:
//   с ассоциативными как-то все на так в плане алгоритмов
#include "visuality/view.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
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
TEST(STL, Remove_fun) {
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

  coll.erase(remove_if(
      coll.begin(), coll.end(),
                      bind2nd(less<int>(), 
                      4)),
             coll.end());
  print_elems(coll, "removed < 4: ");

  // удаления с копированием

}

TEST(stl, unique_fun) {

}
