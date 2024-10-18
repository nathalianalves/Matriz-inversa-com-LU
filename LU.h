#ifndef _LU_
#define _LU_

#include <stdio.h>
#include "estruturas.h"

// Decompoe uma matriz A nas matrizes L e U, em que L armazena os multiplicadores e U armazena o resultado da matriz A após eliminação de Gauss
void decomposeLU(double **A, double **L, double **U, unsigned int n);

/* Resolve um sistema Ax = b, em que os parâmetros são: 
  - L e U: decomposição de A
  - b: termos independentes
  - x: incognitas
  - n: ordem da matriz A
*/
void solveLU (double **L, double **U, double *b, double *x, unsigned int n);

// Retorna em inverse a matriz inversa de A. Retorna 1 para sucesso e 0 para erro de alocação dinâmica.
int invertMatrix(double **A, double **inverse, unsigned int n);

#endif