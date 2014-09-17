// http://www.codeproject.com/Tips/537403/Cplusplus-Prefer-bind-to-bind-st-and-bind-nd
// http://www-h.eng.cam.ac.uk/help/tpl/languages/C++/bind.html
// bind2nd - op(a1, A2_conn)
// bind1st - op(A1_conn, a2)
//
// Note: В алгоритм можно передать и по ссылке, но тогда нужно полностью специфицировать шаблон.

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

#include "visuality/view.h"

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


TEST(STL, BinaryPredicats) {
  //TODO:
  // Важно понять какие совойства должны быть и для каких операций
  // '=='
  //   транзитивность
}

void func(int* p) {
}

// summary:
// p. 303 - не должен изменять состояние

class Nth {
private:
  int nth;
  int count;
public:
  Nth(int n) : nth(n), count(0) {}

  // лучше пердавать по значению или по конст. ссылке.
  // не должны менятся свойства как предиката, но константность лучше сперва поставить
  bool operator() (int) /* must be const, but accamulate? best make const */ {
    return ++count == nth;
  }
};

class IntSequence {
public:
  int value;
public:
  IntSequence(int ini) : value(ini) {}
  int operator()() {
    return value++;
  }
};

TEST(STL, PredicateWithState) {
  IntSequence a(1);
  a();
  a();
  assert(a.value == 3);
  IntSequence b = a;
  assert(b.value == 3);  // так а как состояние обнуляется? меняется копия!

  // функтор != предикат
  // for_each единственная может вернуть предикат - наверное не совсем предикат
}

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

// http://easy-coding.blogspot.ru/2009/07/blog-post_25.html
// функтор быстрее указателя на функцию, но см. комменты

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

