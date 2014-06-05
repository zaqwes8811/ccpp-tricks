
#include <iostream>
#include <list>

#include "matrix.h" 
 
using namespace std;
using std::list;

void foo(matrix mat) {
  cout << "foo: " << mat.get(10, 9) << endl;
}

int main() {
  int i, j;
  matrix darray(100, 100);
  //foo(darray);  // Now not compiled
   
  
  // Iterators test
  list<char> coll;
  
  // Лучше как понял end объявить заранее, но лучше локально
  // http://valera.asf.ru/cpp/book/c05_5.html
  for (
    list<char>::const_iterator pos=coll.begin(), end=coll.end();
    pos != end; ++pos) {}
    
  //end++;  // out of scope
   
}