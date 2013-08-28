//---------------------------------------------------------------------------


#pragma hdrstop

#include "TrRs.h"
#include "FileConst.h" //  константы

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---- конструктор --------------
TUCharArr::TUCharArr(){
   pos=0, posint=0,buf=0;
}
//-------------------------------------------------
int TUCharArr::StrToUnsCharAr(AnsiString bufe){
  pos=0, posint=0,buf=0; // свойства объекта - их нужно сбрасывать
  // ограничение на предаваемую строку 256 байт
  strcpy(store, bufe.c_str());  // пока еще работает
  // нужно как то проверить на ошибки
  longL=strlen(store); // число принятых, но непреобразованных символов
  if(longL==0){
     //"Нет данных для передачи";
     return(0);  // выход из обработчика
  }
  if(longL%3 != 2){ // "AB_FD_AS"
        //ShowMessage("Вводить парами и через пробел");
  	return(1); // выход из обработчика
  }
  // прогноизируем число байтов для отправнки  перезапись переменной
  longL=(int)(longL/3)+1; // важно для записи в порт если есть нули в посылке
  unsigned char *sour=new unsigned char[longL+1];
  for(int i=0;i<longL+1;i++)sour[i]=0;// обнуляем, хотя может и не нужно
  //  sour - пока еще нормальная строка
  while(store[pos] != 0){ // можно и for т.к. спрогноизровали
  	if(store[pos] == ' ')pos++;
  	// calc begin
  	int i=0, j=0, k=1;
  	for(j=0;j<2;j++){ // берем парами
  	  while(store[pos] != KEY[i]){
  	     i++;
  	     if(i==16){
  	       // ShowMessage("Неверный формат данных");
  	        delete [] sour;
  	        return(2);
  	     }
  	   }
  	   buf+=i*(unsigned int)(pow((float)(16),k));// суммируем с накоплением
  	   i=0; // Для поиска по ключу
  	   k--;
  	   pos++;
  	}
  	bait=static_cast<unsigned char>(buf);
  	sour[posint]=bait;
        buf=0;
  	posint++;
	// end of calk
	}
	sour[posint]='\0'; // доделываем строку
        // могут быть нулевые символы и помимо конца строки
// теперь заполняем буффер для отправки
   if(posint > 255){  // передана слишком больная команда
      // ShowMessage("Послка не влезает во входной буффер");
       return(3);
   }
   for(int i=0;i<longL+1;i++){ // сохраняем в свойство объекта
      store[i]=sour[i];
   }
// посылка сфримирована удаляем, то что динамическое
  delete [] sour;
  return(longL);
}
//---------------------------------------------------------
void TUCharArr::GetConSum(unsigned char *bufer, int len){
  cSum[1]='\0';
  akk=0;
  for(int i=0;i<len;i++){
     akk+=static_cast<unsigned int>(bufer[i]);
  }
  cSum[0]=static_cast<unsigned char>(akk%256);
}
//----------------------------------------------------------
int TUCharArr::AddCoSum(){
  GetConSum(store, longL); // посчитали контрольную сумму
  // longL - указывает на нулевой байт строки
  store[longL]=cSum[0]; // Добавили
  return(longL+1);
}
