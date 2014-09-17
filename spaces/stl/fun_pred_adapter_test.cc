// http://www.codeproject.com/Tips/537403/Cplusplus-Prefer-bind-to-bind-st-and-bind-nd
// http://www-h.eng.cam.ac.uk/help/tpl/languages/C++/bind.html
// bind2nd - op(a1, A2_conn)
// bind1st - op(A1_conn, a2)
//
// Note: В алгоритм можно передать и по ссылке, но тогда нужно полностью специфицировать шаблон.

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <gtest/gtest.h>

using std::cout;
using std::endl;
using std::vector;
using std::ostreambuf_iterator;
using std::out_of_range;

TEST(STL, StreamIterators) {
  vector<int> a(5, 8);
  copy(a.begin(), a.end(), std::ostream_iterator<int>(cout, " "));
  cout << endl;
}

TEST(STL, BinaryPredicats) {
  //TODO:
  // Важно понять какие совойства должны быть и для каких операций
  // '=='
  //   транзитивность
}

void func(int* p) {
}

