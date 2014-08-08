//---------------------------------------------------------------------------
#ifndef AnsiProcH
#define AnsiProcH
//---------------------------------------------------------------------------
#include <Classes.hpp> 	// для работы с AnsiString
#include <math.h>
#include "FileConst.h" //  константы
#include "IntStrConv.h"
//---------------------------------------------------------------------------
// работа массивов буззнаковых символов и ансистринг строк
class TAnsiProc // 
{
private:
        // преобразование одного символа uchar -> HL
        int tmp;		// преобразованный символ чар
        int ibuf[2]; 	        // для временного хранения
	AnsiString AOut;        // здесь будет храниться представление
	void uchar2AnsiS(void); // беззнаковое представление
        // перобразование для целых сткрок
	int akk; 			// аккамулятор
        long lakk;
	unsigned char Sum; 	        // для контрольной суммы
        unsigned char SumIn; 	// для контрольной суммы
        // ?? эффективномть вот того что ниже под вопросом
	unsigned char store[255]; 	// хранит результаты преобразования
        // как ее выделить динамически непонятно(если только отдавать память отдельные методом)
	unsigned char *sour;            // указатель на блок динамической памяти
	AnsiString Abuf;		// принятая строка
        int longL;    	// длинна преобразованной строки(число символов)
        // мелочь
        int len;
        int jj;
        int pos;      	// позиция в исходной строке
        int posint;   	// позиция в преобразованной строке
	// методы
	void StrToUnsCharAr(void); 	// преобразует ансисер. во внутренний массив чар
	void AddCoSum(void); 		// добавляем контрольную сумму
        AnsiString Abuff;
public :
        AnsiString FloatToInt(AnsiString); // убирает из строки "цифр" запятую или точку 
	TAnsiProc();
        AnsiString GetAnsiLine(unsigned char); 	// возвращает строку с хекс символом "ХХ"
	unsigned char GetConSum(unsigned char*, int);  // вычисляет контраольную сумму принятого беззнакового массива
                                // данные передает во внешний массив SumIn
	unsigned char GetConSum(void);  // вычисляет контраольную сумму принятого беззнакового массива
                                // выдает данные из внутреннего массива
        bool Compary_cs(void);  // сравнивает внешнюю и внутреннюю контрольные суммы
        // !через strcat соединять строку и КС нельзя
	unsigned char *Astr2UCstr(AnsiString);     // преобразует Анси строку в массив беззнаковых чар(XX_XX->uchar[])
        unsigned char *Astr2UCstr_cs(AnsiString);  // то же, но с добавление контрольной суммы
	int GetLenSend(void); // т.к. массивы могут содержать нулевые байты, но длинна иногда нужна
        unsigned char *GetStat(void);
	// исключения
        // одна на все и связана с неправильным воодом строки
	class NotHex{  }; // исключительная ситуация - не те символы вводиятся для преобр хекс-инт
};
/* пары вызовов
  Astr2UCstr -> (GetConSum,GetLenSend)
  Astr2UCstr_cs -> GetLenSend
  GetConSum(внешний буффер) - отдельная
*/
/* testbench и использование
TAnsiProc AnsiProc;
AnsiString Ainput=Edit3->Text;
unsigned char rd[]={static_cast<unsigned char>(171), static_cast<unsigned char>(69)};
///*
unsigned char *ucbuf;
try{  // провека исключения
  ucbuf=AnsiProc.Astr2UCstr_cs(Ainput);
}
catch(TAnsiProc::NotHex){
// попросить проверить строку на соответстве формату
}
//
int tmp;
//unsigned char cs = AnsiProc.GetConSum();
unsigned char csIn = AnsiProc.GetConSum(rd,2);
bool test =AnsiProc.Compary_cs();
//tmp=static_cast<int>(cs);
int len = AnsiProc.GetLenSend();
for(int i=0;i<len;i++){
   tmp=static_cast<int>(ucbuf[i]);
} //
Edit2->Text=IntToStr(static_cast<int>(ucbuf[len-1]));
//

unsigned char cbuf=static_cast<unsigned char>(StrToInt(Edit2->Text));
AnsiString AinpuXX=AnsiProc.GetAnsiLine(cbuf);
Edit1->Text=AinpuXX;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  AnsiString Settings="";
  TAnsiProc AnsiProc;
  TIntStrConv IntStrConv(4);
  Edit5->Text=AnsiProc.FloatToInt(Edit4->Text);
  int ifreq;
  try{
     ifreq=StrToInt(Edit5->Text);
  }catch(const EConvertError &){
  ShowMessage("Недопустимая строки");
  return;
  }


  // разбиваем  на десятичне знаки
   int buf_array[8];
    for(int i=0;i<8;i++){ // частот всего восемь
       buf_array[7-i]=ifreq%10;
       ifreq/=10;
    }
  // преобразуем
     for(int i=0;i<8;i++){ // разворачивае мчастоты
       IntStrConv.int2hex(buf_array[i]);
       Settings+=AnsiString(IntStrConv.Clast.hexrep);
       if(i%2 !=0)Settings+=" ";
    }
    Edit1->Text=Settings;
*/
#endif
