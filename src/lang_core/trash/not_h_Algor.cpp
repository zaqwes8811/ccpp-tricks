 //анализ помехоустойчивости
 /*if(tmplen != 0){
 
// однократный пуск
   counter=0;// сбрасывем счетчик
   Timer1->Enabled=false;
   // очищаем буфферы
   PurgeComm(COMport, PURGE_TXCLEAR);             //очистить передающий буфер порта
   char otvet[100];  // для ответа
   int sakk=0;    // для контрольной суммы
   int j=0;
   lensend=0;
   for(j=0;j<20;j++){
     sakk++;
     otvet[j]=static_cast<char>(1);
     lensend++;  // байт добавили
   }
   sakk=sakk%16;
   otvet[j]=static_cast<char>(sakk);
   lensend++; // на контрольный символ
   // итоговый буфер записи
   memset(bufwr,0,BUFSIZE);// щчищаем буфер
   int i=0;
   for(i=0;i<lensend+1;i++){      // записываем
     bufwr[i]=otvet[i];
   }
   bufwr[i]='\0';  // на вссякий случай
   i=0;
   // start stream
  writer->Resume();	//активировать поток записи в порт

  ////////////////////\\
  if((static_cast<int>(bufrd[0])==0)&& (slaver==0)){ // команда выдать состояние
    // команда поступила в режиме мастера
    slaver=1;// переходим в режим slave
    AnsiString bufe="12 1A";
    lensend=StrToGlobBufw(bufe,bufwr);
 }
 //////////////////////
 
 ///!!
 /*if(Form1->CheckBox4->Checked == true){ // включен тестовый режим
 //========  вывод параметров состояния ==========
  if((bufrd[0]=='\0') && (cycle == 1)){ // в тестовом режиму
   GetStateSl();   // ответ на команду запрос-состояния
   if(stageState == 0)stageState=1; //
   }
 // подсчет контрольной суммы
   if((stageState == 1) && (cycle == 2)){
     McSum[1]='\0';
     getCSumChArr(bufrd, tmplen-1,McSum); // нужны только информационные символы
     if(McSum[0]==bufrd[tmplen-1]){
      // ShowMessage("Ок");
     }
     stageState=0; //stageState=0;
   }
 //=============
 if(static_cast<unsigned int>(bufrd[0])== 1 && (cycle == 1)){ // в тестовом режиму
   GetSetSl();     // выдаем параметры установки
   if(stageSet == 0)stageSet=1; //
 }
   // подсчет контрольной суммы
   if((stageSet == 1) && (cycle == 2)){
     McSum[1]='\0';
     getCSumChArr(bufrd, tmplen-1,McSum);
     if(McSum[0]==bufrd[tmplen-1]){
       int i=0;
     }
     stageSet=0; //stageState=0;
   }

 //=====================
 if((static_cast<unsigned int>(bufrd[0])== 2)&&(cycle == 1)){
 // в тестовом режиму (эхо-ответ модулятора)
   Echo2();
 }
 
 // ========== загрузка модулятора ==========
  if((static_cast<unsigned int>(bufrd[0])== 3)&&(cycle == 1)){
 // в тестовом режиму (эхо-ответ модулятора)
   Echo3();
 }
 if((static_cast<unsigned int>(bufrd[0])== 3)&&(cycle == 2)){ // модулятор получил эхо
 // в тестовом режиму (эхо-ответ модулятора)
   LoadSet();  // передаем модулятору установки
 }
 // раз дошло до третьего цикла
  if(cycle == 3){ // модулятор должен выдать контрольную сумму
 // в тестовом режиму (эхо-ответ модулятора)
   Check(bufrd, tmplen);  // передаем модулятору установки
}
 if(cycle == 4){ // контроль
 // в тестовом режиму (эхо-ответ модулятора)
    if(bufrd[0]==McSum[0]){
      //ShowMessage("Передача прошла успешно");
    }
 }
 }else{// режим мастера
   // получение парам етров состояни
   if(cycle == 1){  // по сетке отпарвили ноль
     // проверяем контрольную сумму
     McSum[1]='\0';
     getCSumChArr(bufrd, tmplen-1,McSum);
     if(McSum[0]!=bufrd[tmplen-1]){
       ShowMessage("Ошибка связи с модулятором");
     }
     // анаизируем состояние
     AnalyseState();
   //}
   }
   //  параметры установки
   if(cycle == 2){  // по сетке отпарвили ноль
      //void AnaluseSet(void){
   }
   //  эхо при загрузки модулятора
   if(cycle == 3){  // по сетке отпарвили ноль
     if((static_cast<unsigned int>(bufrd[0])== 2)){ // получили эхо

     }
   }
   //  эхо при вводе пераметров
   if(cycle == 4){  // по сетке отпарвили ноль
     if((static_cast<unsigned int>(bufrd[0])== 3)){ // получили эхо
        LoadSet();
     }
   }
   if(cycle == 5){  // по сетке отпарвили ноль

   }
 }
*/

\\\\\\\\\\\\\\\\\\\\\\\\

//=================================
// ------------ slave---------------
/*
void GetStateSl(){  // получить состояние модулятора
  // очищаем буфферы
  PurgeComm(COMport, PURGE_TXCLEAR);             //очистить передающий буфер порта
  memset(bufwr,0,BUFSIZE);// !! щчищаем буфер
  // посылка
  AnsiString SendMax="12 00 C1 01 02 01 02 09";
  lensend=StrToGlobBufw(SendMax,bufwr,255) ;    // преобразуем в массив посылки
  // считаем контрольную сумму
  unsigned char cSum[2]; // место для контрольной суммы
  getCSumChArr(bufwr, lensend, cSum);
  bufwr[lensend]=cSum[0];   // т.к. могут быть нули нужно именно так, а не сцеплять
  lensend++;
  //
  writer->Resume();	//активировать поток записи в порт
}
//---------------------
void GetSetSl(void){ // вывести параметры состояний(slave)
  PurgeComm(COMport, PURGE_TXCLEAR);             //очистить передающий буфер порта
  memset(bufwr,0,BUFSIZE);// !! щчищаем буфер
  // посылка
  AnsiString SendMax="12 01 00 C1 02 01 02 09 11 11 A1";
  lensend=StrToGlobBufw(SendMax,bufwr, 255) ;    // преобразуем в массив посылки
  // считаем контрольную сумму
  unsigned char cSum[2];
  getCSumChArr(bufwr, lensend, cSum);
  bufwr[lensend]=cSum[0];   //
  lensend++;
  //
  writer->Resume();	//активировать поток записи в порт
}
//--------------
void Echo2(void){ // повтор команды
  PurgeComm(COMport, PURGE_TXCLEAR);             //очистить передающий буфер порта
  memset(bufwr,0,BUFSIZE);// !! щчищаем буфер
  // эхо-посылка
  AnsiString SendMax=LOAD_MOD;
  lensend=StrToGlobBufw(SendMax,bufwr,255) ;    // преобразуем в массив посылки
  writer->Resume();	//активировать поток записи в порт
}
//--------------
void Echo3(void){ // повтор команды
  PurgeComm(COMport, PURGE_TXCLEAR);             //очистить передающий буфер порта
  memset(bufwr,0,BUFSIZE);// !! щчищаем буфер
  //
  AnsiString SendMax=INPUT_SET_PARAM;
  lensend=StrToGlobBufw(SendMax,bufwr,255) ;    // преобразуем в массив посылки
  writer->Resume();	//активировать поток записи в порт
}
void Check(unsigned char *buf, int len){ // вычисляем контрольную сумму получки
  PurgeComm(COMport, PURGE_TXCLEAR);
  memset(bufwr,0,BUFSIZE);//
  //
  unsigned char cSum[2];
  getCSumChArr(buf, len,cSum);
  bufwr[0]=cSum[0];
  lensend=1;  // символ всего один
  writer->Resume();	//активировать поток записи в порт
}
//=================================
// ------------ master ---------------

void LoadSet(void){  // загрузить настройки в модулятор
  PurgeComm(COMport, PURGE_TXCLEAR);             //очистить передающий буфер порта
  memset(bufwr,0,BUFSIZE);// !! щчищаем буфер

  AnsiString SendMax="12 01 01 00 02 01 02 A9 02 A9";
  // перекодируем
  lensend=StrToGlobBufw(SendMax,bufwr,255) ;    // преобразуем в массив посылки
  // считаем контрольную сумму
  McSum[1]='\0';  // глобальный буффер
  getCSumChArr(bufwr, lensend,McSum);
  writer->Resume();	//активировать поток записи в порт

}

//-------------------------
*/
 