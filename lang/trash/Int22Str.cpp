//---------------------------------------------------------------------------


#pragma hdrstop

#include "Int22Str.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TInt22Str::TInt22Str(int width)
{
  Clast.hexrep=new char[width/4+1]; 	// важно
  Clast. nibble_arr=new int[width/4];	// !
  Clast.width=width;
}
//-----------------------
TInt22Str::~TInt22Str()
{
 delete [] Clast.hexrep;
 delete [] Clast.nibble_arr;
}
//--------------------------
void TInt22Str::hex2int(char *buf)	// переводим строку в полубайтовый массив
{ 
	Clast.hexrep=buf;
	i=0, j=0;
	while(Clast.hexrep[j] != '\0'){ // строки с х00 будут недочитаны но с х48 все будет нормально
		while(Clast.hexrep[j]!=HEX_DI_KEY[i]){
			i++;
			if(i > 15){ // это признак ошибки
				throw NotHex(); // исключение: введен какой то нетакой символ
			} 
		}
	Clast.nibble_arr[j]=i; // запоминаем отсчет
	j++;
	i=0; 
	}
	Clast.depth=j; // запоминаем число отсчетов
}
//------------------------------
void TInt22Str::int2hex(long sourse)
{
    Clast.sourse = sourse; // принимаем отсчет
    sourse_buf = sourse;
    // при необходимости переводим в дополнительный код
    Q15=pow(2,(Clast.width-1));
    if((sourse >= Q15)||(sourse < -Q15)){
       throw Overflow(); // возникает исключение return неудобно т.к. пока возвр. void
    }
    if(sourse_buf < 0)
	{
        sourse_buf=2*Q15+sourse_buf; //  полностью дополнительный код, но число - uint
    }
    num_halbb=Clast.width/4;    // число символов в шестнадцатеричном представлении
    Clast.depth=num_halbb;
    save=0,  j=0;
    // init
    Clast.hexrep[0]='\0' ;
    pStr[1]='\0';// возможно и не нужно, но чтоб наверняка
    for(int i=0; i<num_halbb; i++)
	{
        save=sourse_buf%16; 			// долгая операция вцелом
        change[num_halbb-i-1]=save;    // от 0-15
        sourse_buf=sourse_buf/16;  	// нужно для проверки не окончение опереции
    }
    // преобразуем в цепочку символов
    for(int i=0; i<num_halbb; i++)
	{
        while(change[i]!= j) // отсчитываем до нужного нам символа
		{  
			j++;
        }
        Clast.nibble_arr[i]=j;
        pStr[0] = HEX_DI_KEY[j];
        j=0; // обязательно обнуление
        strcat(Clast.hexrep,pStr);
    }
 }
//----------------------------------
void TInt22Str::uchar2AnsiS(unsigned char buf){ 	// беззнаковые символы в анли зхекс строку
	Out_set=""; 		// сбрасываем
	tmpt=static_cast<int>(buf);
	// разбираем число
	ibuf[1]=tmpt%16; 	// младший байт заносим вторым элемнтом массива
	tmpt/=16;
	ibuf[0]=tmpt%16; 	// старший в начало
	if(ibuf[0]>9)
	{ 		// добавляем сперва старший 
		switch(ibuf[0])
		{
			case 10: Out_set+="A"; break;
			case 11: Out_set+="B"; break;
			case 12: Out_set+="C"; break;
			case 13: Out_set+="D"; break;
			case 14: Out_set+="E"; break;
			case 15: Out_set+="F"; break;
		}
	} else {
		Out_set+=IntToStr(ibuf[0]);
	}
	if(ibuf[1]>9)
	{ // теперь младший
		switch(ibuf[1])
		{
			case 10: Out_set+="A"; break;
			case 11: Out_set+="B"; break;
			case 12: Out_set+="C"; break;
			case 13: Out_set+="D"; break;
			case 14: Out_set+="E"; break;
			case 15: Out_set+="F"; break;
		}
	}
	else
	{
		Out_set+=IntToStr(ibuf[1]); // просто сцепляем
	}
 }
 //------------------------------
TClaster TInt22Str::GetClaster(void){		// возвращаем кластер
  return(Clast);
}
//------------------------
AnsiString TInt22Str::GetAnsiLine(void){ 	// возвращает строку с хекс символом "ХХ"
  return(Out_set);
}

/*

void IntStrConv::IntIni(int width){
// инциализаця для приема целыз
  Clast.width=width;
  Clast.hexrep=new char[width/4+1];
  Clast.nibble_arr=new int[width/4];
}
void IntStrConv::HexIni(int width){
 // инициализайия для прием строки с hexчислом
  Clast.width=width;
  Clast.hexrep=new char[width/4+1];
  Clast.nibble_arr=new int[width/4];
} */
