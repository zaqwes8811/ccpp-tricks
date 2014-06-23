#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

using std::vector;

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

