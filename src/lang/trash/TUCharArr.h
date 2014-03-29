//---------------------------------------------------------------------------

#ifndef TrRsH
#define TrRsH
#include <Classes.hpp>
#include <math.h>
//---------------------------------------------------------------------------
class TUCharArr{
public:
   unsigned char cSum[2]; // для контрольной суммы
   char store[255]; // хранилище
   // metods
   TUCharArr();
   void GetConSum(unsigned char*, int);  // вычисляет контраольную сумму
     // входноая последовательнсть
     // !размер последовательность может содержать нулевые символы
   int StrToUnsCharAr(AnsiString); // преобразует Анси строку в массив чар(унутренний)
     // !через strcat соединять строку и КС нельзя
   int AddCoSum();
   // можно добавить функцию обратного преобразования
private:
  int pos;      // позиция в исходной строке
  int posint;   // позиция в преобразованной строке
  int longL;    // длинна полезных данных
  unsigned char bait;   // для одного преобразованного символа
  int buf;              // временное хранение int-представления преобразованного байта
  int akk; // аккамулятор
};
#endif
/* testbench
int key=name.StrToUnsCharAr("sdf");
switch(i)
{
case 0:{}break;
}

*/
