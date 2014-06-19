#include <vector>
#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>

using std::cout;
using std::endl;
using std::vector;
using std::ostreambuf_iterator;

class matrix {
public:
  matrix(int r=2, int c=2) {
    nrows_ = r;
    ncols_ = c;
    m_ = new double[r*c];
  }

  double get (int r, int c) const {
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
    //TODO: fill
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
      //TODO: fill
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

  //TODO: disable copy and assign
};

//TODO: deep and shallow copy
//
// http://www.fredosaurus.com/notes-cpp/oop-condestructors/shallowdeepcopy.html - desigin
//
// http://www.fredosaurus.com/notes-cpp/oop-condestructors/copyconstructors.html
// http://stackoverflow.com/questions/1936942/writing-a-deep-copy-copying-pointer-value
//
// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
// http://stackoverflow.com/questions/2657810/deep-copy-vs-shallow-copy
//
// Вообще не понятно, если объкт не владеет, или указатель на нединамическую память или used DI
// http://stackoverflow.com/questions/255612/dynamically-allocating-an-array-of-objects/255744#255744

//TODO: impl. copy by assign or revert, i don't remember + swap

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

/// Требования к объектам
// http://www.amse.ru/courses/cpp2/2011_02_21.html
// wiki
class STLObject {
public:
  // "копия эквив. оригиналу"? но тут похоже логика, что объект тот же
  // '==' реализовывать не обязательно. Просто должен быть точным клоном.
  STLObject(const STLObject& that);
  STLObject& operator=(const STLObject& that);
  ~STLObject();
  //operator==  //TODO: должно быть или нет?
  //operator<  //TODO: in assoc.?
private:
  //TODO: а конструктор может быть приватным?
};

void foo(matrix mat) {

}

TEST(STL, CopyAndAssign) {
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

  // New Step 8:
  //b == c;  // if
  vector<matrix> mat_vec_a;
  vector<matrix> mat_vec_b;
  //mat_vec_a == mat_vec_b;  // для такого сравнения нужно реализовать ==
}

TEST(STL, StreamIterators) {
  vector<int> a(5, 8);
  copy(a.begin(), a.end(), std::ostream_iterator<int>(cout, " "));
  cout << endl;
}

TEST(STL, BinaryPredicats) {
  //TODO:
  // Важно понять какие совойства должны быть и для каких операций
  // '=='
  //   транзитивность
}
