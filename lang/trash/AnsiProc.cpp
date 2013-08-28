//---------------------------------------------------------------------------


#pragma hdrstop

#include "AnsiProc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---- конструктор --------------
TAnsiProc::TAnsiProc(){
   pos=0, posint=0,akk=0;
}
// ================ char символа в анси предсталвение
 void TAnsiProc::uchar2AnsiS(void){ 	// беззнаковые символы в анли зхекс строку
	AOut=""; 		// сбрасываем
	// разбираем число
	ibuf[1]=tmp%16; 	// младший байт заносим вторым элемнтом массива
	tmp/=16;
	ibuf[0]=tmp%16;
	// декодируем	
	if(ibuf[0]>9) // добавляем сперва старший 
	{ 		
		switch(ibuf[0])
		{
			case 10: AOut+="A"; break;
			case 11: AOut+="B"; break;
			case 12: AOut+="C"; break;
			case 13: AOut+="D"; break;
			case 14: AOut+="E"; break;
			case 15: AOut+="F"; break;
		}
	} else {
		AOut+=IntToStr(ibuf[0]);
	}
	if(ibuf[1]>9)
	{ // теперь младший
		switch(ibuf[1])
		{
			case 10: AOut+="A"; break;
			case 11: AOut+="B"; break;
			case 12: AOut+="C"; break;
			case 13: AOut+="D"; break;
			case 14: AOut+="E"; break;
			case 15: AOut+="F"; break;
		}
	}
	else
	{
		AOut+=IntToStr(ibuf[1]); // просто сцепляем
	}
 }
//------------------------
AnsiString TAnsiProc::GetAnsiLine(unsigned char buf){ 	// возвращает строку с хекс символом "ХХ"
  tmp=static_cast<int>(buf);
  uchar2AnsiS(); // операция обработки
  return(AOut);
}
//-------------------------------------------------
void TAnsiProc::StrToUnsCharAr(void){
  pos=0, posint=0,akk=0; // свойства объекта - их нужно сбрасывать
  // ограничение на предаваемую строку 256 байт
   if(Abuf.Length() > 255){     // передана слишком больная команда
       throw NotHex();		// слишком длинная строка
   }
  strcpy(store, Abuf.c_str());  // пока еще работает
  // нужно как то проверить на ошибки
  longL=strlen(store); // число принятых, но непреобразованных символов
  if(longL==0){
        throw NotHex();  //"Нет данных для передачи";
  }
  if(longL%3 != 2){      // "AB_FD_AS"
        throw NotHex();  // неправильный формат
  }
  // предварительные проверки пройдены и теперь
  // прогноизируем число байтов для отправнки  перезапись переменной
  longL=(int)(longL/3)+1; // важно для записи в порт если есть нули в посылке
  sour=new unsigned char[longL+1];
    for(int i=0;i<longL+1;i++)sour[i]=0;// обнуляем, хотя может и не нужно

  //  store - пока еще нормальная строка
  while(store[pos] != 0){ // можно и for т.к. спрогноизровали
  	if(store[pos] == ' ')pos++; // нашли пробел и пропустили
  	int i=0, j=0, k=1;
  	for(j=0;j<2;j++){ // берем парами
  	  while(store[pos] != KEY[i]){  // возможно не очень эффективно и лучше switch
  	     i++;
  	     if(i==16){ // символ не найден
  	        delete [] sour;
		throw NotHex();  // введено что то не то
  	     }
  	   }
           //
  	   akk+=i*(unsigned int)(pow((float)(16),k));// суммируем с накоплением
  	   i=0; // Для поиска по ключу
  	   k--;
  	   pos++;
  	} // пара преобразована
  	sour[posint]=static_cast<unsigned char>(akk); // добавляем в коприлку
        akk=0; // сбрасываем накопитель
  	posint++;
	}
  sour[posint]='\0'; // доделываем строку

  // теперь заполняем буффер для отправки
  for(int i=0;i<longL+1;i++){ 	// сохраняем в свойство объекта
      store[i]=sour[i]; 	// принятую строку затираем
   }
  // посылка сфримирована удаляем, то что динамическое
  delete [] sour; // !! поэтому нужно сохранить
  sour=NULL;
}
//--------- вычисляем контрольную сумму для переданногоей функции массива -------------------------
unsigned char TAnsiProc::GetConSum(unsigned char *bufer, int len){
  akk=0;
  for(int i=0;i<len;i++){
     akk+=static_cast<unsigned int>(bufer[i]);
  }
  SumIn=static_cast<unsigned char>(akk%256);
  return(SumIn);
}
//---- возвращает отдельно контрольную сумму -------
unsigned char TAnsiProc::GetConSum(void){
   GetConSum(store, longL); // посчитали контрольную сумму внутренних даннх
   // она теперь находится во входном буфере
   // ее нужно перенсти во внутерний и выдать
   Sum=SumIn;
   return(Sum);
}
//----------------------------------------------------------
void TAnsiProc::AddCoSum(){
  GetConSum(store, longL);      // посчитали контрольную сумму внутренних даннх
  Sum=SumIn;                    // копируем во внутренний
  store[longL]=Sum;             // Добавили
  longL++;  // ! здесь
}
//=============== получение беззнакового массива ===================
unsigned char *TAnsiProc::Astr2UCstr(AnsiString Ainput){
/*
1. сохраряем строку во внутренний ансистр массив
2. преобразуем
*/
 Abuf=Ainput;
 StrToUnsCharAr();
 return(store);
}
//
unsigned char *TAnsiProc::Astr2UCstr_cs(AnsiString Ainput){
/*
1. сохраряем строку во внутренний ансистр массив
2. преобразуем
3. добавляем контрольную сумму
4. прибавляем к длине 
*/
 Abuf=Ainput;
 StrToUnsCharAr();
 AddCoSum();   // добавляет длинну
 return(store);
}
//--- возвращаем длинну --
int TAnsiProc::GetLenSend(void){
  return(longL);
}
//  сравнивем внутренню и внешнюю контрольные суммы
bool TAnsiProc::Compary_cs(void){
  if(Sum == SumIn){
  return(true);
  }else{
  return(false);
  }
}
//--------------------
AnsiString TAnsiProc::FloatToInt(AnsiString Temp)
{

Abuff="";
len=Temp.Length();
for(jj=1;jj<len+1;jj++){
   if((Temp[jj] == ',')||(Temp[jj] == '.')){
    Temp.Delete(jj,1); // символ с запятой пропускаем
    jj--;
    len--;
   }
  }
 Abuff+=Temp;
 return(Abuff);
}
/////


