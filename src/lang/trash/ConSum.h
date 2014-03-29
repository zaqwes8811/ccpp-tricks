//---------------------------------------------------------------------------

#ifndef ConSumH
#define ConSumH
#include "FileConst.h"
#include <string.h>
//---------------------------------------------------------------------------
class ConSum{ // есть особенность исопльзования
                // если чило полубайтов в последовательноси нечетрое
                // то дополнительно передаем ноль
public:
  ConSum(); 	// конструктор
  void LoadHByte(int);     	// прием по int
  void LoadChar(char );   	// по символу хекс
  char *GetConSum(); 	// возвращает шестнадцатиразрядное чилсло из акк.
						// сброс аккамулятора
// исключение
  class NotHex{  };						
private:
  int ind;      // индикатор типа получнного полубайта; изанч. старший
  int carry;    // перенос из младшего
  int SAH;  // накопитель для старшего разряда
  int SAL;  // накопитель младшего
  char pStrH[2];
  char pStrL[2];
  int j;
  int cout; // счетчик полученный до сброса отсчетов
  int chbuf; // буффер для числа при получении символьных отсчетов
};
#endif

/* testbench
char *p;
CoderSum ConSum; // накопитель
int array[7]={1,1,15,15,15,15,15};
for(int i=0;i<7;i++){
ConSum.LoadHByte(array[i]);
}
p=ConSum.GetConSum();
*/
