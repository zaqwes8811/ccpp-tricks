// http://www.rsdn.ru/forum/cpp/2810409.1 !!

// Third party
#include <gtest/gtest.h>

// @Ref
// 1
// ERROR: не определн new and new[]
class B {
public:
    virtual ~B();
    void operator delete(void*, size_t) throw();
    /*Real static*/ void operator delete[](void*, size_t) throw();
    void f(void*, size_t) throw();

};

class D: public B {
public:
    void operator delete(void*) throw();
    void operator delete[](void*) throw();
};
// @Ref

TEST(Sutter, CheckFile) {
    //D* pd1 = new D;
    //delete pd1;
    //B* pb1 = new D;
    //delete pb1;

    //D* pd2 = new D[10];
    //delete[] pd2;

    // ERROR: Undefined!
    // DANGER: не работать с массивами полиморфно! Лучше vector<> or deque<>
    //B* pb2 = new D[10];
    //delete[] pb2;
}
