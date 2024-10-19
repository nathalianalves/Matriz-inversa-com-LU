#include "timeStamp.h"

double timestamp(){
  struct timeval tp;
  
  gettimeofday(&tp, 0);
  
  return((double)(tp.tv_sec+tp.tv_usec/1000000.0)); 
}