// Note: комментарии в Шилде стр. 31
#include <iostream>
#include <list>
#include <typeinfo>
#include <cstdlib>

using namespace std;  // Bad in header!!

//#define DISPLAY

class OutOfRangeExc {

};

// Перемещение по какому-то массиву.
template <class T> class Iter {
  T *ptr;
  T *end;
  T *begin;
  unsigned length;
public:
  Iter() {
    ptr = end = begin = NULL;
  }

  Iter(T *p, T *first, T *last) {
    ptr = p;
    end = last;
    begin = first;
    length = last - first;
  }

  unsigned size() { return length; }

  T &operator*() {
    if ((ptr >= end) || (ptr < begin))
      throw OutOfRangeExc();
    return *ptr;
  }
  T *operator->() {
    if ((ptr >= end) || (ptr < begin))
      throw OutOfRangeExc();
    return ptr;
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
};

















