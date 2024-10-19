/*  Implementação de funções relacionadas a "marcos" de tempo
    Nathália Nogueira Alves - GRR20232349 - UFPR
*/

#include "timeStamp.h"

// Retorna o "marco" de tempo atual
double timestamp(){
  struct timeval tp;
  
  gettimeofday(&tp, 0);
  
  return((double)(tp.tv_sec+tp.tv_usec/1000000.0)); 
}