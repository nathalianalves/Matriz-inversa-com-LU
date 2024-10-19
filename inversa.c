/*  Main do projeto inversa
    Nathália Nogueira Alves - GRR20232349 - UFPR
*/

#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include "timeStamp.h"  
#include "LU.h"

int main() {
  unsigned int n;
  double **A, **inverse, **residual, residualNorm, timeStamp1, timeStamp2;

  // Seta o arredondamento para baixo e lê a ordem da matriz
  fesetround(FE_DOWNWARD);
  scanf("%d\n", &n);

  // Aloca variáveis e verifica o retorno. Retorna -1 se der erro.
  A = allocateMatrix(n, n);
  inverse = allocateMatrix(n, n);
  residual = allocateMatrix(n, n);
  if ((!A) || (!inverse)) {
    printf("Falha ao alocar memoria\n");
    return -1;
  }

  // Lê a matriz A, da qual vai calcular a inversa
  readMatrix(A, n, n);

  // Configura os timestamps e calcula a inversa da matriz A
  timeStamp1 = timestamp();
  if (!invertMatrix(A, inverse, n))
    return -1;
  timeStamp2 = timestamp();

  // Calcula a matriz dos resíduos e guarda a média das normas de cada coluna em residualNorm
  if (!calculateResidual(A, inverse, residual, n))
    return -1;
  residualNorm = averageNorms(residual, n);

  // Impressões: ordem, matriz inversa, média das normas dos resíduos e o tempo usado no cálculo da inversa
  printf("\n%d\n", n);
  printMatrix(inverse, n, n);
  printf("%.15e\n", residualNorm);
  printf("%.8e\n", timeStamp2-timeStamp1);

  // Desaloca variáveis
  freeMatrix(A, n, n);
  freeMatrix(inverse, n, n);
  freeMatrix(residual, n, n);

  return 0;
}