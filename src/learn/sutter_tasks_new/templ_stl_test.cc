

#include <cassert>
#include <vector>

#include <gtest/gtest.h>

using std::vector;

/// Task 1: Vector

void f(vector<int>& v) {
  v[0];
  v.at(0);
}

TEST(SutterNew, Task1) {
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
    *i;
  }

  // updated
  for (vector<int>::const_iterator i=v.begin(),
      end=v.end();  // reduce extra calc
      i != end;  // < -> !=
      ++i) {
    *i;
  }
}




