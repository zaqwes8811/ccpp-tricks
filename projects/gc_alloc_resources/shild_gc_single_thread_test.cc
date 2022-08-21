// Note: комментарии в Шилде стр. 31

// JetBrains:
//   http://jetbrains.ru/students/events/students-traineeship-in-jetbrains/

#include <gtest/gtest.h>

#include <cstdlib>
#include <iostream>
#include <list>
#include <typeinfo>

using namespace std;  // Bad in header!!

//#define DISPLAY

class OutOfRangeExc {};

// Перемещение по какому-то массиву.
template <class T>
class Iter {
    T *ptr;
    T *end;
    T *begin;
    ptrdiff_t length;

public:
    Iter() { ptr = end = begin = NULL; }

    Iter(T *p, T *first, T *last) {
        ptr = p;
        end = last;
        begin = first;
        length = last - first;
    }

    ptrdiff_t size() { return length; }

    T &operator*() {
        if ((ptr >= end) || (ptr < begin)) throw OutOfRangeExc();
        return *ptr;
    }

    T *operator->() {
        if ((ptr >= end) || (ptr < begin)) throw OutOfRangeExc();
        return ptr;
    }

    Iter operator++() {
        ptr++;
        return *this;
    }

    Iter operator--() {
        ptr--;
        return *this;
    }

    Iter operator++(int notused) {
        T *tmp = ptr;
        ptr++;
        return Iter<T>(tmp, begin, end);
    }

    Iter operator--(int notused) {
        T *tmp = ptr;
        ptr--;
        return Iter<T>(tmp, begin, end);
    }

    // TODO: дописать остаток
};

template <class T>
class GCInfo {
public:
    unsigned refcount;
    T *memPtr;

    bool isArray;
    unsigned arraySize;

    GCInfo(T *mPtr, unsigned size = 0) {
        refcount = 1;
        memPtr = mPtr;
        if (size != 0)
            isArray = true;
        else
            isArray = false;
        arraySize = size;
    }
};

template <class T>
bool operator==(const GCInfo<T> &ob1, const GCInfo<T> &ob2) {
    return (ob1.memPtr == ob2.memPtr);
}
