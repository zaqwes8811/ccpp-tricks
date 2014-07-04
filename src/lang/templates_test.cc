
#include <gtest/gtest.h>

// http://valera.asf.ru/cpp/book/c10.html
template<class Glorp>
Glorp min2(Glorp a, Glorp b)
{
  return a < b ? a : b;
}

TEST(Templates, Min) {
  int i = min2(1, 2);
  int j = i;
}

template<class T, int size>
T min(const T(&r_array)[size])
{
  T min_val = r_array[0];
  for (int i = 1; i < size; ++i)
    if (r_array[i] < min_val)
      min_val = r_array[i];
  return min_val;
}

typedef double Type;  // в шаблоне этот тип перекрыт
template <class Type>
   Type min( Type a, Type b )
{
   // tmp имеет тот же тип, что параметр шаблона Type, а не заданный
   // глобальным typedef
   Type tmp = a < b ? a : b;
   return tmp;
}

template<class Parm, class U>
Parm minus(Parm* array, U value)
{

  typename // без этого думает что умножение
    Parm::name * p;  //
}

/// Task 1
template <class T, class U, class V>  // add U -> class U
   void foo( T, U, V );

template <class T>
  T foo( T* val );  // int *T -> T* val
