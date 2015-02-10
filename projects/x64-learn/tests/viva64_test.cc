#include "heart/config.h"

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace l5 {
// http://www.viva64.com/ru/l/0005/

void foo(unsigned char) {}
void foo(unsigned int) {}
void a(const char *str)
{
  // strlen return size_t!
  // on x64 size_t == unsigned int
  //foo(strlen(str));  // error on x64
}

TEST(Viva64Test, L5) {
  a("hello");

  // FIXME: Danger!
  std::vector<int> v(8, 0);
  int i = v.size();  // gcc4.8 compile without warnings
  EXPECT_EQ(sizeof( size_t ), sizeof( vector<int>::size_type ));
  //EXPECT_EQ(sizeof( size_t ), sizeof( int ));
  ++i;

  // Must be
  ptrdiff_t j = v.size();
  j++;

  for (
       //ptrdiff_t  // signed! delta can be > 0 and < 0
       size_t

       k = 0; k < v.size(); ++k) {
    v[k];
  }

}
}  // space

namespace l6 {
TEST(Viva64Test, L6) {
  size_t pointersCount = 100;
  int **arrayOfPointers = (int **)malloc(pointersCount * 4);

  // deserealization binary data
  //size_t PixelCount;
  //fread(&PixelCount, sizeof(PixelCount), 1, inFile);
}
}
