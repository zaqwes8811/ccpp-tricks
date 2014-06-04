
#include <iostream>

#include "matrix.h" 
 
using namespace std;
void foo(matrix mat) {
  cout << "foo: " << mat.get(10, 9) << endl;
}

int main() {
  int i, j;
  matrix darray(100, 100);
  foo(darray);
   
   
}