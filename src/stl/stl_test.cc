

#include <vector>
#include <iostream>

#include <gtest/gtest.h>

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
  matrix(const matrix& mc) {
    nrows_ = mc.rget();
    ncols_ = mc.cget();
    m_ = new double [nrows_*ncols_];
    //TODO: fill
  }

private:
  int nrows_;
  int ncols_;
  double* m_;

  //TODO: disable copy and assign
};

using std::cout;
using std::endl;

void foo(matrix mat) {

}

TEST(STL, CopyAndAssign) {
  matrix darray(10, 20);
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 20; j++)
      darray.put(i, j, i*j);
  foo(darray);
}
