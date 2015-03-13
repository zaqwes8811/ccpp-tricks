
#include "std_own_ext/std_own_ext.h"

#include <gtest/gtest.h>

#include <memory>
#include <iostream>
#include <utility>

using namespace std;

TEST(Lava, HW1) {

}

TEST(Lava, L3_ptrs) {
  unique_ptr<int> up(new int(8));  // user &&
  unique_ptr<int> up3(new int(8));  // user &&

  // move resources - up - empty!
  unique_ptr<int> up2 = std::move(up);

  up3 = std::move(up2);

  assert(!up);
}
