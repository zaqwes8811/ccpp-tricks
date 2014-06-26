

#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>

using std::vector;
using std::cout;
using std::endl;

/// Task 1: Vector

void f(vector<int>& v) {
  v[0];
  v.at(0);
}

template<class Container, class OutputIterator>
OutputIterator copy_own(const Container& c, OutputIterator result) {
  return std::copy(c.begin(), c.end(), result);
}

TEST(SutterNew, Task1) {
  using std::ostream_iterator;
  using std::copy;

  vector<int> v;
  v.reserve(2);
  //assert(v.capacity() == 2);
  // скорее больше или равно, но вообще проверять смысле нет
  assert(v.capacity() >= 2);  // added

  // !!Compilde and work, but it's error
  //assert(v.size() == 2);  // added
  //v.at(0) = 1;  // added  throw exception
  //v[0] = 1;
  //v[1] = 2;

  // raw
  for (vector<int>::iterator i = v.begin();
       i < v.end(); i++) {
    cout << *i << endl;
  }

  // updated
  for (vector<int>::const_iterator i=v.begin(),  // const better if read only
      end=v.end();  // reduce extra calc
      i != end;  // < -> !=
      ++i) {
      cout << *i << '\n';  // endl сбрасывает буффер
  }

  // high level update - вообще дело вкуса
  // сразу пропадает ряд ошибок.
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\n"));

  // high level - with const_iter
  copy_own(v, ostream_iterator<int>(cout, "\n"));

}




