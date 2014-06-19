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

  // Step 1: add dctor - Error(gcc): double free or corruption (top):
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
  // if not impl.: Error: double free or corruption (top)
  //void // Step 6
  // DANGER: http://stackoverflow.com/questions/752658/is-the-practice-of-returning-a-c-reference-variable-evil
  // http://stackoverflow.com/questions/15968226/returning-tmp-using-references-behaving-differently
  // http://www.thecodingforums.com/threads/return-reference-to-local-variable.285367/
  // !!!http://bytes.com/topic/c/answers/491692-safe-return-local-object
  // Ссылки на лок. пер. возвр. нельзя. Для объектов можно в нек. случаях, но вообще
  // возвращение ссылок на внутренние объекты классов нарушает инкпасуляцию.
  matrix&  // есть еще одно копирование
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

    // Step 6: Runtime Error(gcc): The program has unexpectedly finished.
    return *this;  // !!
  }

private:
  int nrows_;
  int ncols_;
  double* m_;

  //TODO: disable copy and assign
};

class holder {
public:
  const matrix& get() const { return mat_; }
private:
  matrix mat_;
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
  b = h.get();  // assign
  matrix d = h.get();  // copy ctor
  const matrix& ref_d = h.get();  // а ничего не вызывает
  b = (ref_d);  // assign
  const matrix k(ref_d);  // copy ctor
}

TEST(STL, StreamIterators) {
  vector<int> a(5, 8);
  copy(a.begin(), a.end(), std::ostream_iterator<int>(cout, " "));
  cout << endl;
}
