#include "heart/config.h"

#include <gtest/gtest.h>

#include <vector>

#include <limits.h>

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

namespace l6_7 {
bool FooFind(char *Array, char Value,
             size_t Size)
{
  // FIXME: Danger! no warnings gcc 4.8 - need keys compilar
  for (unsigned i = 0; i != Size; ++i)
    if (i % 5 == 0 && Array[i] == Value)
      return true;
  return false;
}

TEST(Viva64Test, L6) {
  size_t pointersCount = 100;
  int **arrayOfPointers = (int **)malloc(pointersCount * 4);

  // deserealization binary data
  //size_t PixelCount;
  //fread(&PixelCount, sizeof(PixelCount), 1, inFile);
}

// magic
TEST(Viva64Test, L9) {
  // 1
  size_t N = 5;
  size_t ArraySize
      = N * sizeof(intptr_t);
      //= N*4;  // BAD

  // http://stackoverflow.com/questions/1464174/size-t-vs-intptr-t
  // http://stackoverflow.com/questions/6326338/why-when-to-use-intptr-t-for-type-casting-in-c
  intptr_t* Array = (intptr_t* )malloc(ArraySize);


  // 2
  const size_t ARRAY_SIZE = 7;
  size_t values[ARRAY_SIZE];
  memset(values, 0, ARRAY_SIZE *
         sizeof(size_t)  // better sizeof(values)
         //4 // BAD
         );

  // 3
  size_t n, r;
  n = n >> (
             //32  // 4*8  // BAD
             // http://stackoverflow.com/questions/3200954/what-is-char-bit
            CHAR_BIT * sizeof(n)
             - r);

  // 4
  //BAD
  // https://software.intel.com/en-us/forums/topic/348745
#if defined(_WIN64) || defined(__amd64__)
  #define CONST3264(a) (a##ll)
  //i64)  // Windows
#else
  #define CONST3264(a)  (a)
#endif
  const size_t M =
      //0xFFFFFFF0u;  // all except 4 first is 1
      ~CONST3264(0xFu);

  // 5
//#define INVALID_RESULT (0xFFFFFFFFu)  // BAD if (r == -1)
#define INVALID_RESULT (size_t(-1))  // Good
}
}
