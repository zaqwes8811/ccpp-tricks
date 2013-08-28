/**
  file : matrixFirst.cpp
*/
#include "matrixFirst.h"
//#include "Top.h" 
using std::cout;
using std::endl;
/// ///
myMatrix::myMatrix(myMatrix &mc)
{
  _nrows = mc.rget();
  _ncols = mc.cget();
  _m = new double[_nrows*_ncols];
  for(int i = 0; i < _nrows; i++)
    for(int j = 0; j < _ncols; j++)
      put(i, j, mc.get(i, j));
  cout << "copy" << endl;
}


/// ///
myMatrix::myMatrix(int r, int c)
{
  _nrows = r; _ncols = c;
  _m = new double[r*c];
  cout << "constr" << endl;
}
/// /// 
myMatrix::~myMatrix()
{
  //delete [] _m;
  delete _m;
  //cout << "memory free" << endl; 
  cout << "dest" << endl;
}
/// ///
double myMatrix::get(int r, int c)
{
  return _m[r*_ncols+c];  // не двухмерный, а похож
}
/// ///
void myMatrix::put(int r, int c, double d)
{
  _m[r*_ncols+c] = d;
}
/// ///
int myMatrix::rget()
{
  return(_nrows);
}
int myMatrix::cget()
{
  return(_ncols);
}
 
