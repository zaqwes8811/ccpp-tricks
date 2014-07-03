// Crosscompilation:
// http://stackoverflow.com/questions/20574808/how-to-check-arm-none-linux-gnueabi-g-support-for-c11
// http://blog.worldofcoding.com/2014/05/cross-compiling-c11-without-going-madder.html
//
// С++11 не совместим с C++03. А с C++98?
//
// Move in
// http://stackoverflow.com/questions/3106110/what-is-move-semantics
// http://blog.smartbear.com/c-plus-plus/the-biggest-changes-in-c11-and-why-you-should-care/
// http://lin-techdet.blogspot.ru/2013/03/c11-rvalue.html
// !!!https://cloudtips.org/introduction-to-rvalue-references.html
//
// http://sergeyteplyakov.blogspot.ru/2012/05/c-11-faq.html

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
