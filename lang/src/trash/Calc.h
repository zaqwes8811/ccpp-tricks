//---------------------------------------------------------------------------

#ifndef CalcH
#define CalcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//#include <math.h>
#include <string.h>
#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
//#include <windows.h>

#include <shellapi.h>

//

#include "ConSum.h"
#include "GenHarm.h"
#include "IntStrConv.h"


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TRadioButton *Cosin;
        TRadioButton *ByteAndHalb;
        TRadioButton *FullByte;
        TRadioButton *TwoByte;
        TRadioButton *Sinus;
        TRadioButton *SCosin;
        TGroupBox *GroupBox3;
        TListBox *Messager;
        TGroupBox *GroupBox4;
        TEdit *Edit1;
        TButton *Button3;
    TButton *Button4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FullByteClick(TObject *Sender);
        void __fastcall ByteAndHalbClick(TObject *Sender);
        void __fastcall TwoByteClick(TObject *Sender);
        void __fastcall SinusClick(TObject *Sender);
        void __fastcall CosinClick(TObject *Sender);
        void __fastcall SCosinClick(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

        char *myint2hex(char*, int,int);
        // хорошо бы задать по умолчания(на форме отметка не помогает)
        int WIDTH; // разрадность данных ?задвать можно ли здесь
        int TYPECALK;
        int Quest; // размер массива данных, который необходимо получить
        int Lon[8];
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
