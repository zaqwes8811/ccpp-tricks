//---------------------------------------------------------------------------

#ifndef GenHarmH
#define GenHarmH
#include <vcl.h>
#include <math.h>

#include "FileConst.h"
//---------------------------------------------------------------------------
class THarmGen{
public:
   THarmGen(int, int);//
  ~THarmGen();
  struct Claster{
    int NumPoint; // каждый         // число точек дл€ всех сигналов одно
    int Width;            // разр€дность данных - максимиу 16
  } Clast;
  // внутренние буфферы и вычислители
  void GenSinQ();
  void GenCosIQSin();
  void GenCosIQNSin(); // последовтельность отсчетов(I-QIQ) последовательности вставлены одна в одну начина€  с синуса
   int *SinCos;
private:
  int Q15;
  int j;
};
// переинициализайци€ потом поэтому все параметры задаем в конструкторе
//void GenIni(int size_air, int width_air);
#endif
