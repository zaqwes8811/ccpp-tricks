/*

For a class object, this could entail
setting up internal mechanisms for virtual functions and virtual base classes, runtime type information, and other
type-dependent information (see Gotchas #53 and #78). Assignment is the process of replacing the existing state of a
well-defined object with a new state. Assignment doesn't affect internal mechanisms that implement type-dependent
behavior of an object. Assignment is never performed on raw storage.

 */

#include <gtest/gtest.h>

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

TEST(G, Nx) 
{
  // Initialize not assign
  SloppyCopy<int> sloppy;
  f(sloppy);  // init, not assign
}

/// Scoping!!! no reuse args

/// DANGER: Assign and inh.

/// Virtuality mem. map

// Gotcha #54: Copy Constructor Base Initialization
class M {
public:
  M();
  M( const M & );
  ~M();
  M &operator =( const M & );
  // . . .
};
class B {
public:
  virtual ~B();
  
protected:
  B();
  B( const B & );
  B &operator =( const B & );
// . . .
};

class D: public B {
  M m_;
};
