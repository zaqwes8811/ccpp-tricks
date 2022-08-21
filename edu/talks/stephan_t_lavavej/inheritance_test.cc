// http://alenacpp.blogspot.ru/2005/03/blog-post.html !!!
// http://www.gotw.ca/gotw/031.htm
// http://habrahabr.ru/post/51229/ C++ MythBusters. Миф о виртуальных функциях
//
// vtable -
// http://www.programmerinterview.com/index.php/c-cplusplus/how-vtables-work/
//
// TODO: как работает полиморфизм в С++?

#include <iostream>

// Third party
#include <gtest/gtest.h>

using std::cout;
using std::endl;

class VDtor {
public:
    virtual ~VDtor() = 0;
};

VDtor::~VDtor() {}

class VDtorImpl : public VDtor {
public:
    virtual ~VDtorImpl() {}  // Могу определить, а могу и нет
};

// VDtorImpl::~VDtorImpl() { }

TEST(Lang, PureVirtualDtor) {
    // 33/M35 - а класс с виртуальным деструктором будет компилироваться?
    // TODO:
    // VDtor anstr;  // не создасться
    VDtorImpl impl;
}

// Как запретить наследование - нужно ли? Может быть лучше protected
//   для нужд тестирования. В С++ вызов защищенного конструктора не прост -
//   можно вызвать только в списке иниц.
// http://wincode.org/tip/deny-inheritance-virtual-lock
// http://forum.sources.ru/index.php?showtopic=153352
// http://alenacpp.blogspot.ru/2006/03/blog-post_11.html
//
// Нельзя наследовать, но создавать то хочется!
class OnlyDynamic {
    ~OnlyDynamic();

public:
    // …
};

class Derived : public OnlyDynamic {};

// Plan B
class Lock  // «запирающий» класс
{
    friend class Usable;

    Lock() {}

    Lock(const Lock &) {}

public:
};

class Usable : public virtual /*!!!*/ Lock  // «финальный» класс
{
public:
    Usable() { cout << "Usable!"; }
};

class Derived2 : public Usable {};  // формально не запрещено

TEST(Lang, DisableInh) {
    // Derived2 d; // must not compiled
    Usable u;
    // Derived2 *p = new Derived2;  // !!! можно!
}

// http://www.gotw.ca/gotw/040.htm
TEST(Lang, ControlledPolymorphism) {}

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

/// Virtual and multi inh.
// http://www.amse.ru/courses/cpp1/2010.05.14.html
// http://cpp.com.ru/lippman/c18.html
class Parent {};

// единый общий под объект базового класса Parent, а не каждый свою!
class Child1 : virtual public Parent {};

class Child2 : virtual public Parent {};

class GrandChild : public Child1, public Child2 {};

// Next ier.
class Animal {
public:
    void eat() {}  // Метод определяется для данного класса
                   //...
};

class Mammal : virtual public Animal  // !
{
public:
    int getHairColor();
    //...
};

class WingedAnimal : virtual public Animal  // !
{
public:
    void flap();

    void eat() { cout << "Wind\n"; }
    //...
};

// A bat is a winged mammal
class Bat : public Mammal, public WingedAnimal {};  //<--- обратите внимание, что метод eat() не переопределен в Bat

class A {
public:
    virtual void f();
};

class B {
public:
    virtual void f();
};

class C : public A, public B {
public:
    virtual void fA();

    virtual void fB();
};

TEST(Core, VirtInh) {
    Bat bat;

    // вызывается перекрытая!
    bat.eat();  // без виртуальности нет однозначности
}

/// override and overload
// http://logic.pdmi.ras.ru/~smal/aptu/cpp10/2010_11_26.html

namespace lavavej_4 {
// Lava Inh
// http://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Core-C-/Stephan-T-Lavavej-Core-C-4-of-n
// Avoid!
//
// Static type and dyn. type
//
// virtuality check on runtime - it's scary
// override for c++11 - virtual not equal override
// final for c++11

class Base {
public:
    virtual ~Base() {}

    int b;

    // NEED IT
    Base() {}

private:
    // NEED IT
    Base(const Base &);  // it delete other ctors
    Base &operator=(const Base &);
};

class Derived : public Base {
public:
    Derived() {}
};

TEST(Lava, Inh) {
    // Base
    Derived  // can to!
        *p = new Derived;
    // Base b2 = *p;  // slice - need make base noncopyble
}

// NVI - may be good way use inh
// !! Can call private throuth Base*
}  // namespace lavavej_4
