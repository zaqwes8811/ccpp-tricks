/**
  file : mysystime.h
  abs. : job with time
  con. : #include "mysystime.h"
*/
/*

*/
#include <iostream>
/*
  abs. : класс с часами
*/
//namespace myns{
class myclk
{
  public: 
    myclk(int h, int m, int s); // класс теперь "богатый" констр. по ум.
      // нужно создавать самим
    myclk();  // иначе без арг. не создать
    void disp();
    void clkset(int h, int m, int s);
    void tick();
  private:
    void _sw();
    int _hour, _min, _sec;  //
};
extern myclk mclk;  // просто объявления, чтобы видеть в разных местах
//}
//
//extern 
//myclk mclk;
//

