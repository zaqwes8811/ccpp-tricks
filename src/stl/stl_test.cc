

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
