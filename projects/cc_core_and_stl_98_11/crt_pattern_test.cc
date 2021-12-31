// в контейнерах не работает

#include <gtest/gtest.h>

template<class Derived>
class Base {
public:
    void g() { f(); }

private:
    void f() { static_cast<Derived*>(this)->f(); }
};

class Derived1 : public Base<Derived1> {

//private:
public:
    void f() {}
};
//...

class Derived2 : public Base<Derived2> {

//private:
public:
    void f() {}
};
//...


TEST(Idioms, CRT) {
    Derived1* p1 = new Derived1;
    p1->g();

    Base<Derived1>* p2 = new Derived1;
}