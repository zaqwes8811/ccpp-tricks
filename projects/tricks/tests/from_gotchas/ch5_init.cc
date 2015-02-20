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
  M() {}
  M( const M & );
  ~M() {}
  M &operator =( const M & );
  // . . .
};
class B {
public:
  virtual ~B() {}
  
protected:
  B() {}
  B( const B & );
  B &operator =( const B & );
// . . .
};

class D: public B {
public:
  D() {}
  ~D() {}
  D( const D & init) : 
    // DANGER: вызываются обычные конструкторы, а не копирующие, если иниц. только xp_
    B(init), m_(init.m_),  // !!!
    xp_(new int(*init.xp_)) {}
    
  D &operator =( const D & rhs) {
    // !!!
    B::operator=(rhs);  // обязательно, иначе вызовутся конструкторы по умолчанию
    m_ = rhs.m_;
    
    //
    delete xp_;
    xp_ = new int(*rhs.xp_);
    return *this;
  }
private:
  M m_;
  //X 
  int* xp_; // new data member
};

TEST(G, g55) {
  D d;
  //D o = d;
}

namespace g56 {
class Y {
public:
  Y( int ) {
    cout << "ini\n";
  }
  ~Y() {}
  
  // Don't call!! GCC4.7
  Y( const Y & )
  { abort(); }

};

struct {
  char b_[sizeof(Y)];
} aY; // aligned buffer as big as a Y

class X {
public:
  X( int ) {}
  ~X() {}
// . . .
private:
  X( const X & );
};


// не понял - лучше инициализация таки?
TEST(G, g56) {
  //typedef int Y;
  Y a( 1066 );
  Y b = Y(1066);
  /*
  // May be?
  Y temp( 1066 ); // initialize temporary
  Y b( temp ); // copy construction
  temp.~Y(); // destructor activation
  */
  Y c = 1066;

  //
  //new (&aY) Y(1066); // create temp
  //Y d( reinterpret_cast<Y &>(aY) ); // copy ctor
  //reinterpret_cast<Y &>(aY).~Y(); // destroy temp
  
  X a1( 1066 ); // OK
  //X b1 = 1066; // error!
  //X c1 = X(1066); // error!

}
}

namespace g57 {
class Y {
public:
  // DANGER: where explicit
  Y( int ) {}
  ~Y() {}
private:
  Y( const Y & );
  // . . .
};
void f( Y yFormalArg ) {
// . . .
}


TEST(G, g57) {
  // Direct arg. init.
  //f(118);
}
}

namespace g58 {
// computational constructors 

  
}
