//---------------------------------------------------------------------------

#ifndef IntStrConvH
#define IntStrConvH
#include <vcl.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
#include "FileConst.h"
//---------------------------------------------------------------------------
class IntStrConv{ 

public :
// ограничения диапазонов и контроль чтения-записи массивов
 IntStrConv(int);   // выделяет память под массивы
 ~IntStrConv();

 void int2hex(long);  //
 void hex2int(char *);   // [xxxxx\0]
 struct Claster{
   // входы
   long sourse; // полученное и хранимое число
   int  width; // разрядность хранимого числа
   // выходы
   char *hexrep; // максимальное предсталяемое число 2 в 16
   int *nibble_arr; // представление байтами
   int depth; // число символов в хекс-представлении
   } Clast;
};
//1. перевод из хекса в знаковый инт

//2. переконфигугация
 //void
 //void IntIni(int);   // инициализация для вычислений int->hex
 //void HexIni(int);    //hex->int
#endif

