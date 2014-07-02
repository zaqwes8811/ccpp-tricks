// Crosscompilation:
// http://stackoverflow.com/questions/20574808/how-to-check-arm-none-linux-gnueabi-g-support-for-c11
// http://blog.worldofcoding.com/2014/05/cross-compiling-c11-without-going-madder.html
//
// С++11 не совместим с C++03. А с C++98?

#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

// http://www.artima.com/cppsource/rvalue.html

TEST(Cpp11, SimpleLambda) {
  std::vector<int> someList;
  int total = 0;
  std::for_each(someList.begin(), someList.end(), [&](int x) {
    total += x;
  });
}
