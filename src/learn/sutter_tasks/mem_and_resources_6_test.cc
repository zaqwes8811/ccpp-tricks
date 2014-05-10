// Memory types:
//   http://www.rsdn.ru/forum/cpp/2810409.1 !!
//
// Свой new:
// http://www.rsdn.ru/forum/cpp/359892.flat
// Есть в "Современном проектировании" Александрески
//
// Маерс 55:
//
// http://www.amse.ru/courses/cpp2/2011_03_21.html
// StackOv.:
//   http://stackoverflow.com/questions/7824264/why-does-operator-deletes-signature-take-two-parameters
//   http://stackoverflow.com/questions/7149461/why-would-one-replace-default-new-and-delete-operators
//
// Standart:
//   http://stackoverflow.com/questions/7194127/how-should-i-write-iso-c-standard-conformant-custom-new-and-delete-operators/
//
// Xackep.ru:
//   http://www.xakep.ru/post/54481/
//   http://www.xakep.ru/post/54726/

// C++
#include <stdexcept>

// Third party
#include <gtest/gtest.h>

using std::bad_alloc;

// @Ref
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

// 4
class X {
public:
  void * operator new(size_t s, int) throw(bad_alloc) {
    return ::operator new(s);
  }
};

// TODO: Это типа менеджера памяти?
class SharedMemory {
public:
  static void* Allocate(size_t s) {
    return 0;  // OsSpecificSharedMemAllocation(s);
  }
  static void Deallocate(void* p, int i=0) {
    // OsSpecificSharedMemDeallocation(p, i);
  }
};

class Y {
public:
  void * operator new(size_t s, SharedMemory& m) throw(bad_alloc) {
    return m.Allocate(s);
  }

  // Он не парный что ли?
  void operator delete(void* p, SharedMemory& m, int i) throw() {
    m.Deallocate(p);
  }
};

/*
// ERROR: Переопределен глобальный оператор!!
void operator delete(void* p) throw() {
  SharedMemory::Deallocate(p);
}
void operator delete(void* p, std::nothrow_t&) throw() {
  SharedMemory::Deallocate(p);
}*/
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

  //B b;
  typedef void (B::*PWF)(void*, size_t);
  PWF p1 = &B::f;
  //PWF p2 = &B::operator delete;  // delete is static by default
}
