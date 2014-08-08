/**
  file : noCrossTime.h
  
  con. : #include "noCrossTime.h"
*/

#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
//#include "comVar.h"
//
//namespace myns{
//using namespace myns;
extern timer_t gTimerid; 
void start_timer(void);
void timer_callback(int sig);
void stop_timer(void);
//}

