/**
  file : main.cpp
  
  zzz: 
    1. передача в функция по значению и по ссылке. Конструктор коприрования
*/

/// ///
#include "Top.h"
#include "matrixFirst.h"
using std::cout;
using std::endl;
/// ///
const int NOFCOLS = 100;
const int NOFROWS = 100;
void foo(myMatrix mat)
{
  cout << "foo: " << mat.get(10,9) << endl;
}

/// ///
int main()
{
  int i, j;
  myMatrix darray(NOFROWS, NOFCOLS);
  for(i = 0; i < NOFROWS; i++)
    for(j = 0; j < NOFCOLS; j++)
      darray.put(i, j, i*j);
  foo(darray);
//  cout << "Timer delete!" << endl;
}




