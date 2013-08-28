//---------------------------------------------------------------------------


#pragma hdrstop

#include "IntStrConv.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
IntStrConv::IntStrConv(int width){
  Clast.hexrep=new char[width/4+1];
  Clast.nibble_arr=new int[width/4];
  Clast.width=width;
}
//-----------------------
IntStrConv::~IntStrConv(){
 delete [] Clast.hexrep;
 delete [] Clast.nibble_arr;
}
//--------------------------
void IntStrConv::hex2int(char *buf){
Clast.hexrep=buf;
  int i=0, j=0;
  while(Clast.hexrep[j] != '\0'){
    while(Clast.hexrep[j]!=HEX_DI_KEY[i]){
      i++;
      if(i > 16){
      i=16;
      break;} // это признак ошибки
    }
  Clast.nibble_arr[j]=i;
  j++ ;
  i=0;
  }
  Clast.depth=j;
}
//------------------------------
void IntStrConv::int2hex(long sourse){
    Clast.sourse = sourse; // принимаем отсчет
    int sourse_buf = sourse;
     // 2. предполагаема€ разр€дность входных данных
     // при необходимости переводим в дополнительный код
     long Q15=pow(2,(Clast.width-1));
     if(sourse_buf < 0){
          sourse_buf=2*Q15+sourse_buf; //  полностью дополнительный код, но число - uint
     }
      char pStr[2];   // временное хранилище
      int  change[10] ; // ƒл€ перестановки массива
      int num_halbb=Clast.width/4;    // число символов в шестнадцатеричном представлении
      Clast.depth=num_halbb;
      int save=0,  j=0;
      // init
      Clast.hexrep[0]='\0' ;
      pStr[1]='\0';// возможно и не нужно, но чтоб наверн€ка
      for(int i=0; i<num_halbb; i++){//while(test != 0){ // пока не станет нулю
         save=sourse_buf%16; // долга€ операци€ вцелом
         change[num_halbb-i-1]=save;    // от 0-15
         sourse_buf=sourse_buf/16;  // нужно дл€ проверки не окончение опереции
         }
      // преобразуем в цепочку символов
      
      for(int i=0; i<num_halbb; i++){
           while(change[i]!= j){   // отсчитываем до нужного нам символа
           j++;
           }
           Clast.nibble_arr[i]=j;
           pStr[0] = HEX_DI_KEY[j];
           j=0; // об€зательно обнуление
            strcat(Clast.hexrep,pStr);
      }

 }
 //----------------------------------
   // дл€ переконфигурации без
/*void IntStrConv::IntIni(int width){
// инциализац€ дл€ приема целыз
  Clast.width=width;
  Clast.hexrep=new char[width/4+1];
  Clast.nibble_arr=new int[width/4];
}
void IntStrConv::HexIni(int width){
 // инициализайи€ дл€ прием строки с hexчислом
  Clast.width=width;
  Clast.hexrep=new char[width/4+1];
  Clast.nibble_arr=new int[width/4];
} */
