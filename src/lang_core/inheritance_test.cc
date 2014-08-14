// http://alenacpp.blogspot.ru/2005/03/blog-post.html !!!
// http://www.gotw.ca/gotw/031.htm

#include <iostream>

// Third party
#include <gtest/gtest.h>

using std::cout;
using std::endl;

class VDtor {
public:
  virtual ~VDtor() = 0;
};

VDtor::~VDtor() {

}

class VDtorImpl : public VDtor {
public:
  virtual ~VDtorImpl() {}  // Могу определить, а могу и нет
};

//VDtorImpl::~VDtorImpl() { }

TEST(Lang, PureVirtualDtor) {
  // 33/M35 - а класс с виртуальным деструктором будет компилироваться?
  // TODO:
  //VDtor anstr;  // не создасться
  VDtorImpl impl;

}

// Как запретить наследование - нужно ли? Может быть лучше protected
//   для нужд тестирования. В С++ вызов защищенного конструктора не прост - можно вызвать только в списке иниц.
// http://wincode.org/tip/deny-inheritance-virtual-lock
// http://forum.sources.ru/index.php?showtopic=153352
// http://alenacpp.blogspot.ru/2006/03/blog-post_11.html
//
// Нельзя наследовать, но создавать то хочется!
class OnlyDynamic 
{ 
  ~OnlyDynamic();
 public: 
  // …
};

class Derived: public OnlyDynamic
{ };

// Plan B
class Lock                                // «запирающий» класс
{ 
  friend class Usable;
  Lock() { }
  Lock(const Lock&) { }
  
public:
};

class Usable: public virtual/*!!!*/ Lock        // «финальный» класс
{ 
public:
  Usable() { cout << "Usable!"; }
};

class Derived2: public Usable {};        // формально не запрещено


TEST(Lang, DisableInh) {
  //Derived2 d; // must not compiled
  Usable u;
  //Derived2 *p = new Derived2;  // !!! можно!
}

// http://www.gotw.ca/gotw/040.htm
TEST(Lang, ControlledPolymorphism) {

}

// http://alenacpp.blogspot.ru/2006/03/blog-post_11.html
// Про private наследование
/*
class A{};
class B: private A{};
class C: public B{
public:
  A* a;
};
*/

// class CDerived : private CBase - pub and prot -> private
// class CDerived : protected CBase - pub and prot -> prot
// class ...

/// Virtual inh.
