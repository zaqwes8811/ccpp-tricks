//---------------------------------------------------------------------------


#pragma hdrstop

#include "GenHarm.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
THarmGen::THarmGen(int size_air, int width_air ){   // выделем память под !все массивы
    // для экономии можно сохранять  в один
       SinCos=new int[size_air*2]; // пусть будет сразу удвоенного размер
       Clast.NumPoint=size_air;
       Clast.Width=width_air;
       Q15=pow(2,(Clast.Width-1));
       j=0;
 }
 //---
 THarmGen::~THarmGen(){   // выделем память под !все массивы
       delete [] SinCos; // пусть будет сразу удвоенного размер
 }
 //------------
 void THarmGen::GenSinQ(){  // генератор одного периода синусоиды
 for(int i=0; i<Clast.NumPoint; i++){
   SinCos[i]=(int)((Q15-1)*sin(2*PI*i/Clast.NumPoint));
 }
}//-------------------------------
 void THarmGen::GenCosIQSin(){
 j=0;
 for(int i=0; i<2*Clast.NumPoint; i=i+2){
   SinCos[i]=(int)((Q15-1)*cos(2*PI*j/Clast.NumPoint));    // генератор одного периода синусоиды
   SinCos[i+1]=(int)((Q15-1)*sin(2*PI*j/Clast.NumPoint));
   j++;
 }
}//-------------------------------------------
 void THarmGen::GenCosIQNSin(){
    j=0;
 for(int i=0; i<2*Clast.NumPoint; i=i+2){
   SinCos[i]=(int)((Q15-1)*cos(2*PI*j/Clast.NumPoint));    // генератор одного периода синусоиды
   SinCos[i+1]=-(int)((Q15-1)*sin(2*PI*j/Clast.NumPoint));
   j++;
 }
}//----  */
