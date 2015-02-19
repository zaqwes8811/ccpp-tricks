#include "heart/config.h"

#include <gtest/gtest.h>

#include <vector>

#include <limits.h>

using namespace std;

namespace l5 {
// http://www.viva64.com/ru/l/0005/
// http://www.viva64.com/ru/a/0004/ summary 20 errors

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

  size_t size = v.size();
  for (
       ptrdiff_t  // signed! delta can be > 0 and < 0
       //size_t
       k = 0; k <
          size
       ; ++k) {
    //v[k];
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


ptrdiff_t SetBitN(ptrdiff_t value, unsigned bitNum) {
  ptrdiff_t mask =
      //1 << bitNum;  // BAD
      ptrdiff_t(1) << bitNum;
  return value | mask;
}

struct BitFieldStruct {
  unsigned short a:15;
  unsigned short b:13;
};

TEST(Viva64Test, L11) {
  BitFieldStruct obj;
  obj.a = 0x4000;
  size_t addr = obj.a << 17; //Sign Extension
  printf("addr 0x%Ix\n", addr);
  //Output on 32-bit system: 0x80000000
  //Output on 64-bit system: 0xffffffff80000000  // clang - 80...
}

// addr! 13!!
// arr[i] == arr + i
TEST(Viva64Test, L13) {
  {
  // !!!memsize types only!!!
  unsigned short a16, b16, c16;
  char* pointer;
  pointer += a16 * b16 * c16;  // to int -> ovf -> ptrdiff
  pointer +=
      static_cast<ptrdiff_t>(a16) *
      static_cast<ptrdiff_t>(b16) *
      static_cast<ptrdiff_t>(c16);

    // segfault - x64
    // First of all diff signed types
    int A = -2;  // to uint on calc
    unsigned B = 1;

    int array[5] = { 1, 2, 3, 4, 5 };
    int *ptr = array + 3;
    ptr = ptr + (A + B); //Invalid pointer value on 64-bit platform
    //printf("%i\n", *ptr); //Access violation on 64-bit platform
  }

  {
    // segfault - x64
    const size_t size = 12;
    char *array = new char[12];
    char *end = array + size;
    for (
         // http://www.viva64.com/en/a/0050/
         // http://stackoverflow.com/questions/4377308/c-size-t-or-ptrdiff-t
         ptrdiff_t  // strange - why no warning - != not < or >
         //size_t
         //unsigned
         i = 0; i != size; ++i)
    {
      /*const
          //int
          ptrdiff_t
          one = 1;
      end[-i - one] = 0;  // bad on x64
      */
    }
  }
}
typedef ptrdiff_t TCoord;  // not just int
class Region {
  float *array;
  TCoord Width, Height, Depth;
  float GetCell(TCoord x, TCoord y, TCoord z) const;
  //...
};
float Region::GetCell(TCoord x, TCoord y, TCoord z) const {
  return array[x + y * Width + z * Width * Height];
}


//extern
char *begin, *end;
unsigned GetSize() {
  return end - begin;  // !! diff!!
}

void foo(ptrdiff_t delta) {}

TEST(Viva64Test, L17) {
  int x, y, z;
  ptrdiff_t SizeValue = x * y * z;  // all to ptrdiff_t()

  // 2
  {
  ptrdiff_t val_1 = -1; unsigned int val_2 = 1;  // extend to greater! it's diff on platforms
  if (val_1 > val_2)
    printf ("val_1 is greater than val_2\n");
  else
    printf ("val_1 is not greater than val_2\n");
  }

  {
    ptrdiff_t val_1 = -1;
    size_t val_2 = 1;
    if (val_1 > val_2)
      printf ("val_1 is greater than val_2\n");
    else
      printf ("val_1 is not greater than val_2\n");
  }

  // 3
  int i = -2;
  unsigned k = 1;
  foo(i + k);
}

struct MyStruct
{
  bool m_bool;
  char *m_pointer;
  int m_int;
};
struct MyStructSmall
{
  // size fall...
  char *m_pointer;
  int m_int;
  bool m_bool;
};

// struct size
// Note: no need forever
TEST(Viva64Test, L23) {
  cout << sizeof(MyStructSmall) << endl;
}

TEST(Viva64Test, L24) {
  // !! IT Can work! x64 registres can catch small var
  //size_t N = ...
  //for (int i = 0; i != N; ++i)
  //{
     //...
 // }
}


}
