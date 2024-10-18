#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include "LU.h"

int main() {
  unsigned int n;
  double **A, **inverse;

  fesetround(FE_DOWNWARD);
  scanf("%d\n", &n);

  A = allocateMatrix(n, n);
  inverse = allocateMatrix(n, n);
  if ((!A) || (!inverse)) {
    printf("Falha ao alocar memoria\n");
    return -1;
  }

  readMatrix(A, n, n);

  if (!invertMatrix(A, inverse, n))
    return -1;

  printf("\n%d\n", n);
  printMatrix(inverse, n, n);

  freeMatrix(A, n, n);
  freeMatrix(inverse, n, n);

  return 0;
}