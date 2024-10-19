#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include "timeStamp.h"  
#include "LU.h"

int main() {
  unsigned int n;
  double **A, **inverse, **residual, residualNorm, timeStamp1, timeStamp2;

  fesetround(FE_DOWNWARD);
  scanf("%d\n", &n);

  A = allocateMatrix(n, n);
  inverse = allocateMatrix(n, n);
  residual = allocateMatrix(n, n);
  if ((!A) || (!inverse)) {
    printf("Falha ao alocar memoria\n");
    return -1;
  }

  readMatrix(A, n, n);

  timeStamp1 = timestamp();
  if (!invertMatrix(A, inverse, n))
    return -1;
  timeStamp2 = timestamp();

  if (!calculateResidual(A, inverse, residual, n))
    return -1;
  residualNorm = averageNorms(residual, n);

  printf("\n%d\n", n);
  printMatrix(inverse, n, n);
  printf("%.15e\n", residualNorm);
  printf("%.8e\n", timeStamp2-timeStamp1);

  freeMatrix(A, n, n);
  freeMatrix(inverse, n, n);
  freeMatrix(residual, n, n);

  return 0;
}