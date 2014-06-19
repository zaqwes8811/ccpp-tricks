

#include <vector>
#include <iostream>

#include <gtest/gtest.h>

using std::cout;
using std::endl;

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
  void operator=(const matrix& mc) {
    cout << "Call assign operator" << endl;
    delete [] m_;
    nrows_ = mc.rget();
    ncols_ = mc.cget();
    m_ = new double[nrows_ * ncols_];
    //TODO: fill
  }

private:
  int nrows_;
  int ncols_;
  double* m_;

  //TODO: disable copy and assign
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
}
