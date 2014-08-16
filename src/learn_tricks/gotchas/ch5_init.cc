/*

For a class object, this could entail
setting up internal mechanisms for virtual functions and virtual base classes, runtime type information, and other
type-dependent information (see Gotchas #53 and #78). Assignment is the process of replacing the existing state of a
well-defined object with a new state. Assignment doesn't affect internal mechanisms that implement type-dependent
behavior of an object. Assignment is never performed on raw storage.

 */

#include <iostream>

using namespace std;

template <typename T>
class SloppyCopy {
public:
  // ctors 
  // Есть есть хотя бы один конструктор, то автоматом уже не генерится?
  SloppyCopy() { }
  
  // copy
  // Если однн объявлен, то остальные все равно генеряться!
  SloppyCopy& operator=(const SloppyCopy&); 
  
  // Note: compiler default 
  SloppyCopy(const SloppyCopy& t) : ptr(t.ptr) {
    cout << "copy ctor" << endl;
  }
  
private:
  T* ptr;
};

void f(SloppyCopy<int> s) {
  
}

int main() 
{
  // Initialize not assign
  SloppyCopy<int> sloppy;
  f(sloppy);  // init, not assign
  
  return 0;
}