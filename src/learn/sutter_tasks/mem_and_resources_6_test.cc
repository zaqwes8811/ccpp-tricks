// http://www.rsdn.ru/forum/cpp/2810409.1 !!

// Third party
#include <gtest/gtest.h>

// @Ref
// 1
// Error: не определн new and new[]
class B {
public:
    virtual ~B();
    void operator delete(void*, size_t) throw();
    void operator delete[](void*, size_t) throw();
    void f(void*, size_t) throw();

};

class D: public B {
public:
    void operator delete(void*) throw();
    void operator delete[](void*) throw();
};
// @Ref

TEST(Sutter, CheckFile) {

}
