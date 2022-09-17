
// Boost.SharedPtr thread safity:
//   http://stackoverflow.com/questions/14482830/stdshared-ptr-thread-safety
//   http://stackoverflow.com/questions/9127816/stdshared-ptr-thread-safety-explained
//   http://stackoverflow.com/questions/13638526/why-does-boostshared-ptr-bother-with-atomic-reference-counting-when-its-not-t

// Own learn
// http://msdn.microsoft.com/ru-ru/library/z3f89ch8.aspx
// STL - реализация ссылочной семантики

// DANGER: циклическое неудаление при использовании shared_ptr. "Подводные
// камни" http://habrahabr.ru/post/191018/ А ведь собственный указатель может
// быть и без пары shared_ptr/weak_ptr

#include <gtest/gtest.h>

#include <ostream>

namespace {
template <class T>
class CountedPtr {
private:
    T *ptr;
    long *count;

public:
    explicit CountedPtr(T *p = 0) : ptr(p), count(new long(1)) {}

    // Copy - по значению
    CountedPtr(const CountedPtr<T> &p) : ptr(p.ptr), count(p.count) {
        ++(*count);  // счетчик уже нового объекта?
    }

private:
    // throw()
    void dispose() {
        if (--(*count) == 0) {
            delete count;
            delete ptr;
        }
    }
};

// http://www.parashift.com/c++-faq/ref-count-simple.html

TEST(ImT, STLBookSmartPtr) {}

TEST(ImT, AdaptBoostIntrusivePtr) {}
}  // namespace
