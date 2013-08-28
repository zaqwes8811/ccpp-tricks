/**
  file : mysystime.cpp
  abs. : job with time
*/
/*

*/
#include "Top.h"
using std::cout;
using std::endl;
//using namespace myns;

myclk::myclk(int h, int m, int s)
{
  _hour = h; _min = m; _sec = s;
}
myclk::myclk()  // constr. default
{
  _hour = 0; _min = 0; _sec = 0;
}
/// ///
void myclk::disp()
{
  _sw(); cout << _hour; cout << ':';
  _sw(); cout << _min; cout << ':';
  _sw(); cout << _sec; cout << 
  '\n';
  //'\r';
}
/// ///
void myclk::_sw()
{
  cout.fill('0'); cout.width(2);
}
/// ///
void myclk::clkset(int h, int m, int s)
{
  _hour = h; _min = m; _sec = s;
}
/// ///
void myclk::tick()
{
  if(_sec == 59)
  {
    _sec = 0; _min++;
  }
  else _sec++;
///
  if(_min == 60)
  {
    _min = 0; _hour++;
  }
}
