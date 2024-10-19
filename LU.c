#include "LU.h"

// Encontra e retorna o indice da linha que contem o pivo
unsigned int findPivot(double **A, unsigned int row, unsigned int n) {
  unsigned int pivot = row;

  for (unsigned int i = row+1; i < n; i++) {
    if (abs(A[i][row]) > abs(A[pivot][row]))
      pivot = i;
  }

  return pivot;
}

// Troca, na matriz A e no vetor swaps, as linhas row1 e row2
void swapRows(double **A, unsigned int *swaps, unsigned int row1, unsigned int row2) {
  double *tempRow;
  unsigned int temp;

  tempRow = A[row1];
  A[row1] = A[row2];
  A[row2] = tempRow;

  temp = swaps[row1];
  swaps[row1] = swaps[row2];
  swaps[row2] = temp;
}

// Aplica as trocas de linhas feitas em U em b. swaps contem a ordem das linhas em LU (depois de todas as trocas).
void applySwapsToB(double *b, unsigned int *swaps, unsigned int n) {
  double temp[n];

  for (unsigned int i = 0; i < n; i++)
    temp[i] = b[i];

  for (unsigned int i = 0; i < n; i++) {
    if (swaps[i] != i)
      b[i] = temp[swaps[i]]; 
  }
}


// Decompoe uma matriz A nas matrizes L e U, em que L armazena os multiplicadores e U armazena o resultado da matriz A após eliminação de Gauss
void decomposeLU(double **A, double **L, double **U, unsigned int *swaps, unsigned int n) {
  unsigned int iPivot;

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
    iPivot = findPivot(U, i, n);
    if (i != iPivot) 
      swapRows(U, swaps, i, iPivot);
    

    for (unsigned int k = i + 1; k < n; k++) {
      double m = U[k][i] / U[i][i];
      L[k][i] = m;
      U[k][i] = 0.0;
      for (unsigned int j = i+1; j < n; j++) {
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
  unsigned int *swaps; 

  // Alocações - matrizes e vetores
  L = allocateMatrix(n, n);
  U = allocateMatrix(n, n);
  identity = allocateMatrix(n, n);
  x = (double*) malloc(sizeof(double) * n);
  b = (double*) malloc(sizeof(double) * n);
  swaps = (unsigned int*) malloc(sizeof(unsigned int) * n);
  if ((!L) || (!U) || (!identity) || (!x) || (!b) || (!swaps)) {
    printf("Falha ao alocar memoria.\n");
    return 0;
  }

  for (unsigned int i = 0; i < n; i++)
    swaps[i] = i;

  // L e U recebem a decomposição de A
  decomposeLU(A, L, U, swaps, n);

  // A matriz identidade é definida
  initializeIdentityMatrix(identity, n);
  
  // Loop principal
  for (unsigned int i = 0; i < n; i++) {
    // Vetor b recebe a "coluna atual" da matriz identidade
    for (unsigned int j = 0; j < n; j++) {
      b[j] = identity[i][j];
    }

    // Faz as trocas de linha feitas na matriz U no vetor B
    applySwapsToB(b, swaps, n);

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

int calculateResidual(double **A, double **inverse, double **residual, unsigned int n) {
  double **identity;

  identity = allocateMatrix(n, n);
  if (!identity) {
    printf("Não foi possível alocar memória.\n");
    return 0;
  }

  initializeIdentityMatrix(identity, n);

  multiplyMatrices(A, inverse, residual, n);
  subtractMatrices(residual, identity, residual, n);

  // Desalocar a matriz identidade após o uso
  freeMatrix(identity, n, n);

  return 1;
}

double columnNorm(double *residual, unsigned int n) {
  double sum = 0.0;

  for (unsigned int i = 0; i < n; i++) {
    sum += residual[i] * residual[i];
  }

  return sqrt(sum);
}

double averageNorms(double **residual, unsigned int n) {
  double *column, average, sum = 0.0;

  column = (double*) malloc(sizeof(double) * n);
  if (!column) {
    printf("Falha ao alocar memória.\n");
    return 0;
  }

  for (unsigned int j = 0; j < n; j++) {
    // Copia a coluna j da matriz residual
    for (unsigned int i = 0; i < n; i++)
      column[i] = residual[i][j];

    // Soma a norma da coluna
    sum += columnNorm(column, n);
  }

  free(column);

  return sum / n;
}
