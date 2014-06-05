
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
   
  
  // Последовательные контейнеры - упорядоченные
  // std::vector, std::deque, std::list
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
      pos != end;  // DANGER: можно и проскочить! 
      ++pos) 
    {
      
  }
    
  //end++;  // out of scope
  
  // Ассоциативные коллекции - отсортированные коллекции
  // std::set
  // TODO: Ассоциативные контейнеры сортированные?
  typedef set<int, greater<int> > IntSet;
  
  /// Intervals  
  // несколько интервалов
  // TODO: begin, end, begin1! при копировании вычислчется по перовому!!
  //   поэтому длина второго должна быть не меньше длины первого.
  // Есть какие-то итераторы вставки
  // TODO: как работает resize? Что будет если размер больше?
  
  /// Iter Adaptors
  // std::back_inserter, std::front_inserter, std::inserter
  
  /// Streams
  
  /// Modif. algs
  
  /// Functors  и какая-то проблема с ними с 303
  // mem_fun_ref! нужна была как-то
  
  /// POINT
  // требования к элементам контейнера
  
}