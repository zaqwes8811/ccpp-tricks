// ctor_rule_of_three_raii_and_swap_test.cc
//
// "Any class that manages a resource (a wrapper, like a smart pointer) needs
// to implement The Big Three. "
// http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
//
// !!!Need manage only one resouce!!!
//
// Stack:
// http://stackoverflow.com/questions/4172722/what-is-the-rule-of-three?rq=1
// "So when should we declare those special member functions explicitly?
//    When our class manages a resource,
//    that is, when an object of the class is responsible for that resource."
//
// RoT - Для любого класса реализующего RAII!!! Еще есть scoped guards - там нужно запрещать и
//   копирование и присваивание
//
// http://stackoverflow.com/questions/13030272/how-to-implement-an-atomic-thread-safe-and-exception-safe-deep-copy-assignment
// thread-safety and exception-safety
//
// About alloc. on operations
//   http://stackoverflow.com/questions/5072082/assignment-via-copy-and-swap-vs-two-locks
//
// RAII is also less-commonly known as SBRM (Scope-Bound Resource Management).
//
// = - похоже самый тонкореализуемый - и похоже его лучше добавлять последним "The Big Three and A Half(swap)"
//
// Классы с сылками похоже лучше не присваивать. см Саттера 9.N
//
// http://www.slideshare.net/pohjus/c-constructor-copy-constructor-and-assignment-operator-presentation
//
/// ScopeGuard
// - можно передавать и не один аргумент функции
// - можно передвать *this
// - метод можно вызывать с аргументами


#include <stdio.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <new>  // for placement new

#include <gtest/gtest.h>
#include <loki/ScopeGuard.h>

using std::cout;
using std::endl;
using std::vector;
using std::ostreambuf_iterator;

// TODO: new and delete in depth - менеджеры памяти

// TODO:
// ref-counting
// http://www.cplusplus.com/forum/beginner/81321/
// http://www.parashift.com/c++-faq/ref-count-with-cow.html
// http://www.gotw.ca/gotw/043.htm

// TODO:
// полиморфные операторы
// Assign:
// http://stackoverflow.com/questions/669818/virtual-assignment-operator-c

// TODO:
// deep and shallow copy
//
// http://www.fredosaurus.com/notes-cpp/oop-condestructors/shallowdeepcopy.html - desigin
// Вообще похоже должны быть ресурсы и ими объект владеет. Не? А какие ресурсы? Вот мьютекс например?
//
// http://www.fredosaurus.com/notes-cpp/oop-condestructors/copyconstructors.html
// http://stackoverflow.com/questions/1936942/writing-a-deep-copy-copying-pointer-value
//
// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
// http://stackoverflow.com/questions/2657810/deep-copy-vs-shallow-copy
//
// Вообще не понятно, если объкт не владеет, или указатель на нединамическую память или used DI
// http://stackoverflow.com/questions/255612/dynamically-allocating-an-array-of-objects/255744#255744


// TODO:
// impl. copy by assign or revert, i don't remember + swap
// http://en.wikipedia.org/wiki/Assignment_operator_(C%2B%2B)
// Реализация через swap и конструктор копирования

// TODO: Failde ctor
// http://www.gotw.ca/gotw/066.htm

class matrix {
public:
  matrix(int r=2, int c=2) {
    nrows_ = r;
    ncols_ = c;
    m_ = new double[r*c];
  }

  double get(int r, int c) const {
    return m_[r * ncols_ + c];
  }

  void put(int r, int c, double d) {
    m_[r * ncols_ +c] = d;
  }

  // Step 1: add dctor - if copy - Error(gcc): double free or corruption (top):
  // Sln: disable copy
  ~matrix() {
    delete[] m_;
  }

  // Step 2: add copy ctor
  int rget() const { return nrows_; }
  int cget() const { return ncols_; }
  // http://stackoverflow.com/questions/4153527/explicit-copy-constructor-behavior-and-pratical-uses
  // http://stackoverflow.com/questions/11480545/explicit-copy-constructor
  /*explicit*/ matrix(const matrix& mc) {
    cout << "Call copy ctor" << endl;
    nrows_ = mc.rget();
    ncols_ = mc.cget();
    m_ = new double [nrows_*ncols_];
    // TODO: fill
  }

  // Step 4: assign operator
  // if not impl.: on assign - Error: double free or corruption (top)
  //void // Step 6
  // DANGER: http://stackoverflow.com/questions/752658/is-the-practice-of-returning-a-c-reference-variable-evil
  // http://stackoverflow.com/questions/15968226/returning-tmp-using-references-behaving-differently
  // http://www.thecodingforums.com/threads/return-reference-to-local-variable.285367/
  // !!!http://bytes.com/topic/c/answers/491692-safe-return-local-object
  // Ссылки на лок. пер. возвр. нельзя. Для объектов можно в нек. случаях, но вообще
  // возвращение ссылок на внутренние объекты классов нарушает инкпасуляцию.
  //
  // https://isocpp.org/wiki/faq/references
  //
  matrix&  // есть еще одно копирование - да вроде бы нет.
  operator=(const matrix& mc) {
    cout << "Call assign operator" << endl;
    // Step 5:
    if (this != &mc) {  // хоть передан по ссылке, но адрес взять можно
      //cout << "Call assign operator real" << endl;
      delete [] m_;  // a = a - work but...
      nrows_ = mc.rget();
      ncols_ = mc.cget();
      m_ = new double[nrows_ * ncols_];
      // TODO: fill
    }

    // Step 6: if chained - Runtime Error(gcc): The program has unexpectedly finished.
    return *this;  // !!
  }

  /// Other operators
  //==

private:
  int nrows_;
  int ncols_;
  double* m_;

  // TODO: disable copy and assign
};

class holder {
public:
  holder() {}
  const matrix& get() const { return mat_; }

private:
  matrix mat_;

  // disable copy and assign
  holder(const holder& h);
  holder& operator=(const holder& h);
};

void foo(matrix mat) {

}

TEST(Resources, CopyAndAssign) {
  matrix darray(10, 20);
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 20; j++)
      darray.put(i, j, i*j);
  foo(darray);

  // Step 3: on assign call copy ctor?
  matrix a = darray;  // copy ctor !при создании!
  matrix b(a);  // copy ctor

  // Step 4
  matrix c;
  c = a;

  // Step 5
  c = c;  // work but...
  c.put(1, 1, 9);

  // Step 6
  b = a = c;

  // New Step 7:
  cout << "Step 7\n";
  holder h;
  //holder y = h;  // not compiled
  holder y;
  //y = h;  // not compiled
  b = h.get();  // assign
  matrix d = h.get();  // copy ctor
  const matrix& ref_d = h.get();  // а ничего не вызывает
  b = (ref_d);  // assign
  const matrix k(ref_d);  // copy ctor
}

// TODO:
//exception and copy and assign ops
// http://stackoverflow.com/questions/4172722/what-is-the-rule-of-three?rq=1
// http://gotw.ca/gotw/059.htm
// http://www.gotw.ca/gotw/059.htm
class person {
  char* name;
  int age;

public:

  // the constructor acquires a resource:
  // in this case, dynamic memory obtained via new[]
  person(const char* the_name, int the_age)
  {
      name = new char[strlen(the_name) + 1];
      strcpy(name, the_name);
      age = the_age;
  }

  // the destructor must release this resource via delete[]
  ~person()
  {
    delete[] name;
  }

  // 1. copy constructor
  person(const person& that)
  {
      name = new char[strlen(that.name) + 1];
      strcpy(name, that.name);
      age = that.age;
  }

  // 2. copy assignment operator
  person& operator=(const person& that)
  {
      if (this != &that)
      {
          delete[] name;
          // DANGER!!
          // This is a dangerous point in the flow of execution!
          // We have temporarily invalidated the class invariants,
          // and the next statement might throw an exception,
          // leaving the object in an invalid state :(
          name = new char[strlen(that.name) + 1];
          strcpy(name, that.name);
          age = that.age;
      }
      return *this;
  }

  /*
// 2. copy assignment operator
  person& operator=(const person& that)
  {
      char* local_name = new char[strlen(that.name) + 1];
      // If the above statement throws,
      // the object is still in the same state as before.
      // None of the following statements will throw an exception :)
      strcpy(local_name, that.name);
      delete[] name;
      name = local_name;
      age = that.age;
      return *this;
  }
*/
};

int my_fclose ( FILE * stream ) {
  if (stream)
    return fclose(stream);
}

TEST(Resources, ScopedGuard) {
  // http://loki-lib.sourceforge.net/index.php?n=Main.Policy-basedDesign
  // http://www.drdobbs.com/cpp/generic-change-the-way-you-write-excepti/184403758?pgno=2
  //
  // x64 trouble? http://www.viva64.com/en/a/0049/
  using Loki::ScopeGuard;
  using Loki::MakeGuard;

  // http://stackoverflow.com/questions/16922871/why-glibcs-fclosenull-cause-segmentation-fault-instead-of-returning-error
  FILE* topSecret = fopen("_cia.txt", "r");  // failed if file not founded
  assert(topSecret == NULL);
  ScopeGuard closeIt = MakeGuard(my_fclose, topSecret);

  // ...do someting...

  // Помечаем, что действия откатывать не нужно, все прошло хорошо.
  // Но иногда это не нужно.
  //closeIt.Dismiss();  // not need?
}

TEST(Resources, Guards) {
  // Проблема в том, что хотелось бы не использовать Loki.
  // Можно использовать smart_ptrs у функциями удаления, но не у всех есть такая особенность.
  // shared_ptrs лучше для этого не использовать.
  // C+11 - есть
  // Qt - есть
}

template<typename T>
void del_array(T* p) {
  cout << "array deleter\n";
  delete [] p;
}

TEST(Resources, SafeMakeSetArrays) {
  // http://www.drdobbs.com/cpp/generic-change-the-way-you-write-excepti/184403758?pgno=3
  // http://loki-lib.sourceforge.net/index.php?n=Idioms.ScopeGuardPointer
  try {
    /// MayThrow
    int* p = new int[10];
    Loki::ScopeGuard g = Loki::MakeGuard(del_array<int>, p);
    double* table = new double[9];
    Loki::ScopeGuard t = Loki::MakeGuard(del_array<double>, table);
    throw 0;
    //throw 0;

    /// NoThrow
    //g.Dismiss();  // не удаляет

    //int* pp = //g.SafeExecute()
    int* p_state_ = p;
    //std::swap(p, p_new);
  } catch (...) {}
}

namespace no_heap_poly {
// TODO: no-heap poly.
// http://www.barrgroup.com/Embedded-Systems/How-To/Polymorphism-No-Heap-Memory
typedef char Note;
class Instrument {
public:
  virtual void playNote(Note key) = 0;
};

class GenericInstrument : public Instrument {
  // буффер должен быть первой переменной?
  char buf[40];   // max size of Instr.
public:
  virtual void playNote(Note key) {
    this->playNote(key); // enforce late binding
  }
};

class Configuration {

public:
  GenericInstrument i;
};

class Piano : public Instrument {
  int attr;

public:
  Piano() { assert(sizeof(*this) <= sizeof (GenericInstrument)); }
  virtual void playNote(Note key)
  { cout << "Piano " << key << endl; }
};

class Violin : public Instrument {
  int attr1;
  int attr2;
public:
  Violin() { assert(sizeof(*this) <= sizeof (GenericInstrument)); }
  virtual void playNote(Note key)
  { cout << "Violin " << key << endl; }
};

// Mem pool?
static Configuration c1, c2;
}

TEST(Resources, Board) {
  // Placment
  // new http://stackoverflow.com/questions/6783993/placement-new-and-delete

  //Instrument *i;
  //i = new Piano;
  //i->playNote(key);
  using namespace no_heap_poly;

  Instrument* inst = new(&c1.i) Piano;

  inst->playNote('c');
  c1.i.playNote('c');
}







