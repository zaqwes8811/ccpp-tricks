// Validation:
//  http://stackoverflow.com/questions/2062956/checking-if-an-iterator-is-valid
//  http://stackoverflow.com/questions/6954949/how-to-check-if-the-iterator-is-initialized
//
// http://stackoverflow.com/questions/5441893/what-is-singular-and-non-singular-values-in-the-context-of-stl-iterators
//  singular - not init
//  non-singular - Dereferenceable
//  http://stackoverflow.com/questions/3395180/what-is-an-iterators-default-value
//
// "Invalidation of STL Iterators - Angelika Langer"
// http://stackoverflow.com/questions/6438086/iterator-invalidation-rules
//
// Swap and validate
//   http://stackoverflow.com/questions/4124989/does-stdvectorswap-invalidate-iterators
//   https://groups.google.com/forum/#!topic/comp.std.c++/Tmu74awNUUU

#include "projects/view.h"

#include <gtest/gtest.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <list>

using std::cout;
using std::endl;
using std::vector;
using std::ostreambuf_iterator;
using std::out_of_range;

using namespace std;
using namespace view;



// ++it or it++ - второй обязан вернуть старое значение
//TODO: кстати, а как тогда это работает с функциями?

// in -
// out -
// direct - ++
// bidirect - ++ and --
//   random access - vector, deque, string
//   DANGER: list, set, map конец нельзя проверять на <
//   DANGER: шагать большими шагами опасно
//   DANGER: проблема увеличения уменьш. в векторах p. 264, что-то со временными знач
TEST(STL, VectorPPProblem) {
  using std::sort;

  // Сортировка нач. со втрого элемента
  vector<int> coll;  // !!

  // Не переносимая
  if (coll.size() > 1) {
    sort(++coll.begin(), coll.end());
  }

  // Переносимая версия
  if (coll.size() > 1) {
    vector<int>::iterator beg = coll.begin();
    sort(++beg, coll.end());
  }
}

/// Util functions
TEST(STL_Iter, UtilFunc) {
  using std::list;
  using std::advance;

  list<int> coll;

  insert_elems(coll, 1, 9);

  list<int>::iterator pos = coll.begin();
  assert(*pos == 1);

  advance(pos, 3);
  assert(*pos == 4);

  // distance() - первый должен предш. второму или совпадать с ним
}

/// Adaptors
// предбразование в обр. меняет что-то p. 273. Физ поз. сохр., а лог. перемещ
//
// Insert Iter. - итератор вывода - реализ. так что вызывает insert or push_backs
//   and other.
// ++, -- - фиктивные операции
// бывает трех типов - нач., конеч. и общие
TEST(STL_Iter, InsertIters) {
  using std::back_insert_iterator;

  vector<int> coll;

  // inconvenient
  back_insert_iterator<vector<int> > iter(coll);  // при перерасп. станет недейств?
  assert(coll.capacity() == 0);
  *iter = 1;  // перераспределит ли память?
  assert(coll.capacity() == 1);
  iter++;
  *iter = 2;  // just call push_back
  assert(coll.capacity() == 2);

}

TEST(STL_Iter, Ranges) {
  // интервалы должны быть валиндыми 
  //  - не перепутано начало и конец, 
  //  - из одного объекта, 
  //  - не выходят за границы
}

