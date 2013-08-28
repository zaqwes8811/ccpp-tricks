/**
ZZZ:
  1. static and extern
  2. '::' global obj., namespace, области видимости, <ничего>:: - ? глобальный
  3. #include {
      Средством включения текстов служит макрокоманда #include, 
    которая позволяет собрать в один файл
    (единицу трансляции) несколько исходных файлов программы. Команда #include "включаемый-файл
  }
  4. конструкторы
  5. определения и объявления
  6. расположение объектов относительно main()
  7. объединение единиц трансляции
  8. локальные и глобалные объекты
  9. пространство имен по умолчанию

  
*/

/// ///
#include "Top.h"
using std::cout;
using std::endl;
//using namespace myns;
myclk mclk(1, 1, 1);
timer_t gTimerid;
int main()
{
  //::mclk.clkset(0, 59, 59);
  (void) signal(SIGALRM, timer_callback);
  cout << "Watch start." << endl;
  start_timer();
  while(1)
    sleep(100);
    //pause();
  timer_delete(gTimerid);
  cout << "Timer delete." << endl;
}




