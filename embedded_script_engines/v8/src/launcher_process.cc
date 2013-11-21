// C++
#include <iostream>
#include <string>

// Other
#include <v8.h>
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
  // Run
  testing::InitGoogleTest(&argc, argv);
  testing::GTEST_FLAG(print_time) = true;
  RUN_ALL_TESTS();
  return 0;
}
