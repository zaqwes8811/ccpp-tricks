/**
  file : noCrossTime.cpp
  
*/

#include "Top.h"
/**/
using std::cout;
using std::endl;
//using namespace myns;
void start_timer(void)
{
  //
  struct itimerspec value;
  value.it_value.tv_sec = 1;//waits for 5 seconds before sending timer signal
  value.it_value.tv_nsec = 0;

  value.it_interval.tv_sec = 1;//sends timer signal every 5 seconds
  value.it_interval.tv_nsec = 0;
  // собственно создание
  timer_create (CLOCK_REALTIME, NULL, &gTimerid);
  timer_settime (gTimerid, 0, &value, NULL);
}
///
void stop_timer(void)
{
  struct itimerspec value;
  value.it_value.tv_sec = 0;
  value.it_value.tv_nsec = 0;
  value.it_interval.tv_sec = 0;
  value.it_interval.tv_nsec = 0;
  timer_settime (gTimerid, 0, &value, NULL);
}
///
void timer_callback(int sig)
{
  ::mclk.disp(); 
  ::mclk.tick();
}
