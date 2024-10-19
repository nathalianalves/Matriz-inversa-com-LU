#include "estruturas.h"

// Aloca uma matriz rows x columns 
double **allocateMatrix(unsigned int rows, unsigned int columns) {
  double **matrix;

  matrix = (double**) malloc(sizeof(double*) * rows);
  if (!matrix)
    return NULL;

  for (unsigned int i = 0; i < rows; i++) {
    matrix[i] = (double*) malloc(sizeof(double) *columns);
    if (!matrix[i])
      return NULL;
  }

  return matrix;
}

// Desaloca uma matriz rows x columns 
void freeMatrix(double **matrix, unsigned int rows, unsigned int columns) {
  for (unsigned int i = 0; i < rows; i++) 
    free(matrix[i]);

  free(matrix);
}

// Zera todos os elementos de uma matriz
void clearMatrix(double **matrix, unsigned int rows, unsigned int columns) {
  for (unsigned int i = 0; i < rows; i++) 
    for (unsigned int j = 0; j < columns; j++)
      matrix[i][j] = 0;
}

// Zera todos os elementos de um vetor
void clearArray(double *arr, unsigned int n) {
  for (unsigned int i = 0; i < n; i++)
    arr[i] = 0;
}

// Imprime uma matriz
void printMatrix(double **matrix, unsigned int rows, unsigned int columns) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++)
      printf("%.15e ", matrix[i][j]);
    printf("\n");
  }
}

// Preenche uma matriz identidade
void initializeIdentityMatrix(double **matrix, unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      if (i == j)
        matrix[i][i] = 1.0;
      else
        matrix[i][j] = 0.0;
    }
  }
}

void readMatrix(double **matrix, unsigned int rows, unsigned int columns) {
  for (unsigned int i = 0; i < rows; i++)
    for (unsigned int j = 0; j < columns; j++)
      scanf("%le", &matrix[i][j]);
}

void multiplyMatrices(double **A, double **B, double **result, unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      result[i][j] = 0; // Inicializa a matriz resultado
      for (unsigned int k = 0; k < n; k++) {
        result[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

void subtractMatrices(double **A, double **B, double **result, unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      result[i][j] = A[i][j] - B[i][j];
    }
  }
}