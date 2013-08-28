//---------------------------------------------------------------------------

#include <vcl.h>

//
#pragma hdrstop
#include "Calc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;  
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    Edit1->Text=32;
    if(FullByte->Checked == true){WIDTH=8;} // 8 бит
    if(Sinus->Checked == true){TYPECALK=0;} // тип сигнала
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
Application->Terminate(); // выходим
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender){
  AnsiString A;
  int k;
  int j;
  int way=2, addon=1;  // для разделения алгоритмов
  FILE *f;
  int REQUEST=StrToInt(Edit1->Text);// запрос числа отсчетов
  char *buffer = new char[2*REQUEST*(6+1)+1];   // сделаем его чуть длинне массива данных
  // инициализация генераторра
  THarmGen GenI(REQUEST, WIDTH);
  // преобразователи
  IntStrConv ArrConv(WIDTH), AddrConv(16);   // преобразователь в хекс
  CoderSum ICSum;
  AnsiString TYPE;

  /////////////////////
  f = fopen("Harmonics.mif", "w+t");
  *buffer=0;
  //
  TYPE=Edit1->Text;
  Messager->Items->Add("# Параметры: число точек - "+TYPE+", разрядность - "+IntToStr(WIDTH));
  Messager->Perform(LB_SETHORIZONTALEXTENT,512,0);

  // здесь будет обработка информации
  switch(TYPECALK){
    case 0: {
      GenI.GenSinQ();
      way = 2;  addon = 1;
    }break;
    case 1: {
      GenI.GenCosIQSin();
      way = 1;  addon = 2;
    }break;
    case 2: {
      GenI.GenCosIQNSin();
      way = 1;  addon = 2;
    }break;
  }
  Messager->Items->Add("Контрольная сумма для 'AB C' -> XY=AB+C0, с учетом переноса");
  //
  for(j = 0; j < (int)(REQUEST/(8*way)); j++){
    // добавляем адрес
    AddrConv.int2hex(j*(8*way));   // переводим в хекс адрес
    strcat(buffer,AddrConv.Clast.hexrep );
    strcat(buffer," : " );
    // заполняем буффер для записи
    for(int i=j*(8*way)*addon; i<(j+1)*(8*way)*addon; i++){
      ArrConv.int2hex(GenI.SinCos[i]);
      // сохраняем в файл
      if((i%2 == 0)&&(TYPECALK != 0))
        strcat(buffer," " );
      if(TYPECALK == 0)
        strcat(buffer," " );
      strcat(buffer,ArrConv.Clast.hexrep );
      // вычисляем контрольную сумму
      for(k = 0; k < WIDTH/4; k++)
        ICSum.GetHByte(ArrConv.Clast.nibble_arr[k]);
    }  // i
    // добавляем контрольную сумму
    strcat(buffer,"; -- " );
    strcat(buffer,ICSum.GetConSum());
    // сохраняем буффер в файл
    fprintf(f, "%s\n", buffer);
    *buffer=0;
  }  // j

  // если число отчсчетов не кратно 8*way
  // так как нет проблем при вычислении контрольных сумм можносделать в основном цикле
  if(REQUEST%(8*way) != 0){
    // добавляем адрес
    AddrConv.int2hex(j*(8*way));   // переводим в хекс адрес
    strcat(buffer,AddrConv.Clast.hexrep );
    strcat(buffer," : " );
    for(int i=addon*j*(8*way); i<addon*(j*(8*way)+REQUEST%(8*way)); i++){  // последняя строка
      ArrConv.int2hex(GenI.SinCos[i]);
      // сохраняем в файл
      if((i%2 == 0)&&(TYPECALK != 0))
        strcat(buffer," " );
      if(TYPECALK == 0)
        strcat(buffer," " );
      strcat(buffer,ArrConv.Clast.hexrep );
      // вычисляем контрольную сумму
      for(k=0;k<WIDTH/4; k++)
       ICSum.GetHByte(ArrConv.Clast.nibble_arr[k]);
    }  // i
    strcat(buffer,"; -- " );
    strcat(buffer,ICSum.GetConSum());
    fprintf(f, "%s\n", buffer);
    *buffer=0;
  }  // j
  // отчитываемся
  Messager->Items->Add("Результаты сохранены в файле Harmonics.mif");

  // добавляем инфопамция в файл ///////
  fprintf(f, "%s", "-- Число точек: ");
  fprintf(f, "%s", TYPE.c_str());
  fprintf(f, "%s", " ; разрядность:");
  fprintf(f, "%s", IntToStr(WIDTH).c_str());
  switch(TYPECALK){
    case 0:{
      fprintf(f, "%s", " ; тип вычислений - sin");
      fprintf(f, "%s", "\n\n");
    }break;
    case 1:{
      fprintf(f, "%s", " ; тип вычислений - cos+sin");
      fprintf(f, "%s", "\n\n");

    }break;
    case 2:{
      fprintf(f, "%s", " ; тип вычислений - cos-sin");
      fprintf(f, "%s", "\n\n");
    }break;
  }
  // закрываем файл
  fclose(f);
  // очищаем память
  delete [] buffer;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FullByteClick(TObject *Sender)
{   // байтовой представление
     WIDTH=8; // задема видимую  во всей форме пременноуу
     // не получается ли она глобальной
}
//-----------  --------------------------------------------------------------

void __fastcall TForm1::ByteAndHalbClick(TObject *Sender)
{     // 12 разрядов
       WIDTH=12;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TwoByteClick(TObject *Sender)
{        // два байта - слово
   WIDTH=16;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SinusClick(TObject *Sender)
{
   TYPECALK=0; // сичтаем синус
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CosinClick(TObject *Sender)
{
   TYPECALK=1; // сичтаем косинус+синус 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SCosinClick(TObject *Sender)
{
   TYPECALK=2; // сичтаем косинус-синус
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
    Messager->Clear();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
  HANDLE Handl;
  //ShellExecute(Handl, "C:\\WINDOWS\\notepad.exe", "Harmonics.mif", 0, 0, SW_SHOWNORMAL);
  ShellExecute(Handl, "open", "Harmonics.mif", 0, 0, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

