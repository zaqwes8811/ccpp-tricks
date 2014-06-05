
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
  
  // TODO: some.end() возвращает значение или ссылку?
  // Лучше как понял end объявить заранее, но лучше локально
  // http://valera.asf.ru/cpp/book/c05_5.html
  // http://stackoverflow.com/questions/2687392/is-it-possible-to-declare-two-variables-of-different-types-in-a-for-loop
  for (
      // Одного типа
      list<char>::const_iterator pos=coll.begin(), 
      end=coll.end()  // init! assign only one
      ;
      pos != end; ++pos) 
    {
      
  }
    
  //end++;  // out of scope
   
}