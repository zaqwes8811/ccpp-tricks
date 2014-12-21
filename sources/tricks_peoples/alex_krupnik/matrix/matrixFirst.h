/**
  file : matrixFirst.h

  con. : #include "matrixFirst.h"
*/

//#include "Top.h"
#include <iostream>
class myMatrix
{
  public:
    myMatrix(int r, int c);
    ~myMatrix();
    myMatrix(myMatrix &mc);  // констр. копирования
    double get(int r, int c);
    void put(int r, int c, double d);
    int rget();
    int cget();
  private:
    int _nrows;
    int _ncols;
    double *_m;
};
