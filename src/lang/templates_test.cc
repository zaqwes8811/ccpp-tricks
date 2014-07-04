
#include <iostream>

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

template <class T1, typename T2, class T3>
   T1 foo( T2, T3 );

/*inline*/ template <typename T>
inline T foo( T, unsigned int* );

template <class myT/*, class myT*/>
void foo( myT, myT );

template <class T>
 T  foo( T, T );  // перед foo ничего не стояло - это не конструктор - ошибка компил.

// а есть ли ошибка? просто шаблон перекрыл глобальный параметр
typedef char Ctype;
template <class Ctype>
Ctype foo( Ctype a, Ctype b );

// "Какие из повторных объявлений шаблонов ошибочны? Почему?"
// да оба правильные... кажется
template <class Type> Type bar( Type, Type );
template <class Type> Type bar( Type, Type );

template <class T1, class T2> void bar( T1, T2 );
template <typename C1, typename C2> void bar( C1, C2 );

const int lineLength = 12; // количество элементов в строке
void putValues( int *rarray, int sz )
{
  using std::cout;
  cout << "( " << sz << " )< ";
  for (int i = 0; i < sz; ++i ) {
    if ( i % lineLength == 0 && i )
        cout << "\n\t"; // строка заполнена

    cout << rarray[ i ];

    // разделитель, печатаемый после каждого элемента,
    // кроме последнего
    if ( i % lineLength != lineLength-1 && i != sz-1 )
        cout << ", ";
  }
  cout << " >\n";
}

template<class T>
void putValuesTempl( T *rarray, int sz )
{
  using std::cout;
  cout << "( " << sz << " )< ";
  for (int i = 0; i < sz; ++i ) {
    if ( i % lineLength == 0 && i )
        cout << "\n\t"; // строка заполнена

    cout << rarray[ i ];

    // разделитель, печатаемый после каждого элемента,
    // кроме последнего
    if ( i % lineLength != lineLength-1 && i != sz-1 )
        cout << ", ";
  }
  cout << " >\n";
}

TEST(Templates, PutValue) {
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  putValues(a, sizeof a/ sizeof a[0]);

  putValuesTempl(a, sizeof a/ sizeof a[0]);
}
