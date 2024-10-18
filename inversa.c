#include <stdio.h>
#include <stdlib.h>
#include "LU.h"

int main() {
  unsigned int n = 3;
  double **A, **inverse;

  A = allocateMatrix(n, n);
  inverse = allocateMatrix(n, n);
  if ((!A) || (!inverse)) {
    printf("Falha ao alocar memoria\n");
    return -1;
  }

  A[0][0] = 25;
  A[0][1] = 5;
  A[0][2] = 1;
  A[1][0] = 64;
  A[1][1] = 8;
  A[1][2] = 1;
  A[2][0] = 144;
  A[2][1] = 12;
  A[2][2] = 1;

  if (!invertMatrix(A, inverse, n))
    return -1;

  printMatrix(inverse, n, n);

  freeMatrix(A, n, n);
  freeMatrix(inverse, n, n);

  return 0;
}