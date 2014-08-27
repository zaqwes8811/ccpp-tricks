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

