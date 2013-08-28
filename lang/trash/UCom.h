//---------------------------------------------------------------------------

#ifndef UComH
#define UComH
#include <windows.h>
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TComPorts{
 private:
  HANDLE comh;          // дискриптор порта
                        // приватный, при передачи потокам просто копирутся число
 public:
  int CreatePort(AnsiString); // открытие порта (возвращает ошибки)
  HANDLE GetHandCom();          // возвращение дискриптора
  void CloseManag();            // выход из порта
  int LoadSettings(DCB, COMMTIMEOUTS); // получение настроек потров - сразу
                                // структурами
};
/* правила работы с классом
0. создаем экземпляр класса
1. создаем порт
2. получаем хэндл порта(асинхронные режим)настройки не вводим
3. если нужно вводим настройки
4. зактываем порт

*/
#endif
/*
if(ports.CreatePort(ComboBox1->Text)!= 0)            //если ошибка открытия порта
  {
   ports.CloseManag();
  // ListBox1->Items->Add("Не удалось открыть порт") ;       //вывести сообщение в строке состояния
   return;

  }
  Form1->ComboBox1->Enabled = false;
  Form1->ComboBox2->Enabled = false;
 // выставляем таймауты
 timeouts.ReadIntervalTimeout = 150;	 	//таймаут между двумя символами
 timeouts.ReadTotalTimeoutMultiplier = 15;	//общий таймаут операции чтения
 timeouts.ReadTotalTimeoutConstant = 100;      //константа для общего таймаута операции чтения
 timeouts.WriteTotalTimeoutMultiplier = 15;      //общий таймаут операции записи
 timeouts.WriteTotalTimeoutConstant = 150;        //константа для общего таймаута операции записи
  //инициализация структуры DCB
 dcb.BaudRate = 9600;       //задаём скорость передачи 115200 бод
 dcb.fBinary = TRUE;                                    //включаем двоичный режим обмена
 dcb.fOutxCtsFlow = FALSE;                              //выключаем режим слежения за сигналом CTS
 dcb.fOutxDsrFlow = FALSE;                              //выключаем режим слежения за сигналом DSR
 dcb.fDtrControl = DTR_CONTROL_DISABLE;                 //отключаем использование линии DTR
 dcb.fDsrSensitivity = FALSE;                           //отключаем восприимчивость драйвера к состоянию линии DSR
 dcb.fNull = FALSE;                                     //разрешить приём нулевых байтов
 dcb.fRtsControl = RTS_CONTROL_DISABLE;                 //отключаем использование линии RTS
 dcb.fAbortOnError = FALSE;                             //отключаем остановку всех операций чтения/записи при ошибке
 dcb.ByteSize = 8;                                      //задаём 8 бит в байте
 dcb.Parity = 0;                                        //отключаем проверку чётности
 dcb.StopBits = 0;                                      //задаём один стоп-бит
 //
 int key=ports.LoadSettings(dcb,timeouts);
 if(!key){ // какяа то ошибка произошла
    switch(key){   // выясняем какая
      case 1:{
        ports.CloseManag();
       ListBox1->Items->Add("Не удалось считать DCB");
        return;
      } 
      case 2:{
        ports.CloseManag();
        ListBox1->Items->Add("Не удалось установить DCB");
        return;
      }
      case 3:{
        ports.CloseManag();
        ListBox1->Items->Add("Не удалось установить тайм-ауты");
        return;
      }
    }
 }
 // все готово
 Form1->Shape1->Brush->Color=clLime;//
 Form1->Label3->Caption="Порт открыт";
 //-----
 //создать или открыть существующий файл для записи принимаемых данных
 handle = open("test.txt", O_CREAT | O_APPEND | O_BINARY | O_WRONLY, S_IREAD | S_IWRITE);

 if(handle==-1)		//если произошла ошибка открытия файла
  {
   //ListBox1->Items->Add("Ошибка открытия файла");	//вывести сообщение об этом в командной строке
   //Form1->CheckBox3->Checked = false;                                   //сбросить и отключить галочку
  // Form1->CheckBox3->Enabled = false;
  }
 else { //ListBox1->Items->Add("Файл открыт успешно");
 } ////иначе вывести в строке состояния сообщение об успешном открытии файла
 // раз дошло до сюда
 PurgeComm(ports.GetHandCom(), PURGE_RXCLEAR);	//очистить принимающий буфер порта
 // !! потоки
 reader = new ReadThread(true);	                //создать и запустить поток чтения байтов
 reader->Resume();
 reader->FreeOnTerminate = true;                //установить это свойство потока, чтобы он автоматически уничтожался после завершения

 writer = new WriteThread(true);                //создать поток записи данных в порт
 writer->FreeOnTerminate = true;                //установить это свойство, чтобы поток автоматически уничтожался после завершения

 //------
 }else{  // порт закрываем
 SpeedButton2->Caption="Открыть порт";
 Form1->ComboBox1->Enabled = true;
  Form1->ComboBox2->Enabled = true;
  ports.CloseManag();
  //Mport=0; // нужно
  Form1->Shape1->Brush->Color=clRed;
  Form1->Label3->Caption="Порт закрыт";
   //если поток записи существует, подать ему команду на завершение и запустить его, чтобы он выполнил завершение;
 if(writer) //проверка if(writer) обязательна, иначе возникают ошибки;
  {
   writer->Terminate();
   writer->Resume();
  }

 if(reader)reader->Terminate();         //если поток чтения работает, завершить его; проверка if(reader) обязательна, иначе возникают ошибки
 close(handle);				//закрыть файл для записи принимаемых данных
 handle=0;				//обнулить переменную для дескриптора файла

 }        
}
//---------------------------------------------------------------------------
//обработчик закрытия формы
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
 if(reader)reader->Terminate(); 	//завершить поток чтения из порта, проверка if(reader) обязательна, иначе возникают ошибки
 if(writer)writer->Terminate();         //завершить поток записи в порт, проверка if(writer) обязательна, иначе возникают ошибки
 if(ports.GetHandCom())ports.CloseManag();       //закрыть порт
 if(handle)close(handle);               //закрыть файл, в который велась запись принимаемых данных

}
*/
