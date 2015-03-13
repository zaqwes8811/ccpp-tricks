
#include <gtest/gtest.h>


template <typename T>
inline T const& max(T const& a, T const& b) {
  return a < b ? b : a;
}


TEST(BookTemplTest, One) {
  //::max(1, 9.0);  // compil. error
  ::max(1, 9);
}
