#include "LU.h"

// Decompoe uma matriz A nas matrizes L e U, em que L armazena os multiplicadores e U armazena o resultado da matriz A após eliminação de Gauss
void decomposeLU(double **A, double **L, double **U, unsigned int n) {
  
  // Copia A para U e preenche L como uma matriz identidade
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      U[i][j] = A[i][j];
      
      if (i == j)
        L[i][j] = 1.0;
      else 
        L[i][j] = 0.0;
    }
  }

  // Faz eliminação de Gauss na matriz U e armazena os multiplicadores na matriz L
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int k = i + 1; k < n; k++) {
      double m = U[k][i] / U[i][i];
      L[k][i] = m;
      for (unsigned int j = i; j < n; j++) {
        U[k][j] -= U[i][j] * m;
      }
    }
  }
}

/* Resolve um sistema Ax = b, em que os parâmetros são: 
  - L e U: decomposição de A
  - b: termos independentes
  - x: incognitas
  - n: ordem da matriz A
*/
void solveLU (double **L, double **U, double *b, double *x, unsigned int n) {
  double y[n];

  // Resolve Ly = b
  for (unsigned int i = 0; i < n; i++) {
    y[i] = b[i];
    for (unsigned int j = 0; j < i; j++) {
      y[i] -= L[i][j] * y[j];
    }
  }

  // Resolve Ux = y
  for (int i = n-1; i >= 0; i--) {
    x[i] = y[i];
    for (unsigned int j = i+1; j < n; j++) {
      x[i] -= U[i][j] * x[j];
    }
    x[i] /= U[i][i];
  }
}

// Retorna em inverse a matriz inversa de A. Retorna 1 para sucesso e 0 para erro de alocação dinâmica.
int invertMatrix(double **A, double **inverse, unsigned int n) {
  double **L, **U, **identity, *x, *b;

  // Alocações - matrizes e vetores
  L = allocateMatrix(n, n);
  U = allocateMatrix(n, n);
  identity = allocateMatrix(n, n);
  x = (double*) malloc(sizeof(double) * n);
  b = (double*) malloc(sizeof(double) * n);
  if ((!L) || (!U) || (!identity) || (!x) || (!b)) {
    printf("Falha ao alocar memoria.\n");
    return 0;
  }

  // L e U recebem a decomposição de A
  decomposeLU(A, L, U, n);

  // A matriz identidade é definida
  initializeIdentityMatrix(identity, n);
  
  // Loop principal
  for (unsigned int i = 0; i < n; i++) {
    // Vetor b recebe a "coluna atual" da matriz identidade
    for (unsigned int j = 0; j < n; j++) {
      b[j] = identity[i][j];
    }

    // O sistema (com a "coluna atual" da identidade como vetor de termos independentes) é resolvido
    solveLU(L, U, b, x, n);

    // A linha atual (i) recebe a resolução do sistema linear
    for (unsigned int j = 0; j < n; j++)
      inverse[j][i] = x[j];
  }

  // Desalocação - matrizes e vetores
  freeMatrix(L, n, n);
  freeMatrix(U, n, n);
  freeMatrix(identity, n, n);
  free(x);
  free(b);

  return 1;
}