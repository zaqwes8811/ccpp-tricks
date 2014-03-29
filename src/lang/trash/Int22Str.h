//---------------------------------------------------------------------------

#ifndef Int22StrH
#define Int22StrH
//#include <vcl.h>
#include <Classes.hpp> 	// для работы с AnsiString
#include <math.h> 		// вычисление размера
#include <string.h> 	// операщции со строками
#include "FileConst.h" 	// содержит константы
#include "Claster.h"    // с единицей обмена
//нужны ли
//#include <stdio.h>
//#include <stdlib.h>
//#include <fstream.h>
//---------------------------------------------------------------------------

//----------
class TInt22Str // длинное знаковое целое в знаковый массив символов
{
private:
 // верменные переменные
	int sourse_buf;
	long Q15; // нужно для перевода в дополнительный код
	char pStr[2];   // временное хранилище
	int  change[10] ; // Для перестановки массива
	int save;  
	int j; 	// позиция в полученной строке
	int i;	// позиция в строке-ключе
 	int num_halbb; // оценка
	//
	int ibuf[2];
	int tmpt;
 // состояния
	TClaster Clast; 	        // объявляем и создаем
	AnsiString Out_set;     // здесь будет храниться представление
public :
	// ограничения диапазонов и контроль чтения-записи массивов
	TInt22Str(int);   // !динамически выделяет память под массивы
	~TInt22Str();
	//
	class NotHex{  }; // исключительная ситуация - не те символы вводиятся для преобр хекс-инт
        class Overflow{  }; // исключительная ситуация - переполнение
	// методы
	void int2hex(long);  		// полностью заполняют структуру на входе знаковое число!!!
	void hex2int(char *);   	// -"-
	void uchar2AnsiS(unsigned char); // беззнаковое представление
	// возвращение состояний
	TClaster GetClaster(void); 		// возвращаем кластер
	AnsiString GetAnsiLine(void); 	// возвращает строку с хекс символом "ХХ"
};
//-------------------------------
//1. перевод из хекса в знаковый инт
//2. переконфигугация
 //void IntIni(int);   // инициализация для вычислений int->hex
 //void HexIni(int);    //hex->int
#endif

/*  testbench
// Герератор
char invtest[6]={'F', '1', '2', ':', 'A','\0'};
char *test=new char[6];
*test='\0';
int source=StrToInt(Edit1->Text);  // инт преобразованный

// создаем объекты
TInt22Str Conv(StrToInt(Edit2->Text)),DeConv(StrToInt(Edit2->Text)); // передаем параметры конструкторв
//
try{ // преобразуем из инта
  Conv.int2hex(source);
}
catch(TInt22Str::Overflow){
  ShowMessage("Exception(TInt22Str::Overflow):Переполнение");
  return;
}
try{  // преобразование из массива
   DeConv.hex2int(invtest);
}
catch(TInt22Str::NotHex){
    ShowMessage("Exception(TInt22Str::NotHex):Недопустимый символ");
    return;
}
// проверка АНСИ
Conv.uchar2AnsiS(static_cast<unsigned char>(179)); // изменяет состояние
Edit3->Text=Conv.GetAnsiLine();     // выводит состояние
// Анализатор
char* bufer=Conv.GetClaster().hexrep;
int* ib=DeConv.GetClaster().nibble_arr;
for(int i=0;i<5;i++){
  int t=ib[i];
}
// Освобождение
 delete [] test;

*/

