//---------------------------------------------------------------------------


#pragma hdrstop

#include "UCom.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
int TComPorts::CreatePort(AnsiString namecom){  // открывем порт
  comh = CreateFile(namecom.c_str(),  // открываем порт
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        NULL);
  // проверка на ошибки
  if(comh == INVALID_HANDLE_VALUE)            //если ошибка открытия порта
  {
     return(1); // ошибка открытия
  }
  return(0); // ошибка открытия
}
//---------------------
void TComPorts::CloseManag(){  // закрываем
     CloseHandle(comh);
     comh=0;
}
//---------------
HANDLE TComPorts::GetHandCom(){ // просто возовращаем дескриптор
  return(comh);
}
//---------------------------------------
int TComPorts::LoadSettings(DCB dcb, COMMTIMEOUTS timeouts){  //
  dcb.DCBlength = sizeof(DCB);  //в первое поле структуры DCB необходимо занести её длину, она будет использоваться функциями настройки порта для контроля корректности структуры  GetCommState(comh, &dcb);
  //считать структуру DCB из порта
 if(!GetCommState(comh, &dcb))
  {
   CloseManag(); //если не удалось - закрыть порт и вывести сообщение об ошибке в строке состояния
   return(1);  //
  }
  // Загружаем
  if(!SetCommState(comh, &dcb))	//если не удалось - закрыть порт и вывести сообщение об ошибке в строке состояния
  {
   CloseManag();
   return(2);
  }
  //записать структуру таймаутов в порт
 if(!SetCommTimeouts(comh, &timeouts))	//если не удалось - закрыть порт и вывести сообщение об ошибке в строке состояния
  {
    return(3);
  }
 //установить размеры очередей приёма и передачи
 SetupComm(comh,2000,2000);
 // все прошло успешно
 return(0);
}
