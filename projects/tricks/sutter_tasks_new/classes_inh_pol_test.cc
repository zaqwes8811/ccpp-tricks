
#include <string>

#include <gtest/gtest.h>

using std::string;

/// Task 14:
class A {
public:
    A(const string& s) {}

    string f() {
        return "hello";
    }
};

class B : public A {
public:
    B() : A(
        s = f()  // obj A not exist? s not exist too
    ) {}

private:
    string s;
};

TEST(SutterNew, Inh) {
    //B b;  // SEG...
}

class B1 {
};

class V1 : public B1 {
};

// http://stackoverflow.com/questions/419943/virtual-inheritance
class D1 : virtual public V1 {
};

class B2 {
};
