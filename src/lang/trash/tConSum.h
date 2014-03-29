//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Analyser.h"
#include "IntStrConv.h"
#include "ConSum.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
Edit1->Text=-32768;
Edit2->Text=16;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
char invtest[5]={'8', '0', '0', '0', '\0'};
char invtest2[5]={'0', '0', '0', '1', '\0'};
char *test=new char[6];
int *testint=new int[6];
//
*test='\0';
int source=StrToInt(Edit1->Text);
//
IntStrConv Conv(StrToInt(Edit2->Text)), DeConv(StrToInt(Edit2->Text)); // передаем параметры конструкторв
//Conv.IntIni(StrToInt(Edit2->Text));
Conv.int2hex(source);
DeConv.hex2int(invtest);
int r=0;
for(int i=0; i<4; i++){
   r=Conv.Clast.nibble_arr[i];
   r=DeConv.Clast.nibble_arr[i];
}


 delete [] test;
 delete [] testint;
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
char *p;
CoderSum ConSum; // накопитель
int array[7]={1,1,15,15,15,15,15};
for(int i=0;i<7;i++){
ConSum.GetHByte(array[i]);
}
if((5%2)==1)ConSum.GetHByte(0); // добавляем один отсчет
   p=ConSum.GetConSum();

}
//---------------------------------------------------------------------------

