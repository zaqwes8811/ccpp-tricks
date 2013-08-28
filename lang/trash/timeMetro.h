/**
  File: timeMetro.h

  Abstract:
    классы предназначенные для изменения(интервалов времени
    или еще чего-либо)

  Nib:
    - получение величины системного тика
*/
#ifndef timeMetroH
#define timeMetroH
// libs ///
#include <windows.h>

class intervalsMetro {
  LARGE_INTEGER timerFrequency;
  LARGE_INTEGER timerStart;
  LARGE_INTEGER timerStop;
public:
  intervalsMetro();
};
/**
  Abst.: класс для измерения временных интервалов
*/


#endif
 