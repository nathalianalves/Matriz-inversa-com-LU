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
      printf("%.4f ", matrix[i][j]);
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