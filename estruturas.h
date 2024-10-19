#ifndef _ESTRUTURAS_
#define _ESTRUTURAS_

#include <stdio.h>
#include <stdlib.h>

// Aloca uma matriz rows x columns 
double **allocateMatrix(unsigned int rows, unsigned int columns);

// Desaloca uma matriz rows x columns 
void freeMatrix(double **matrix, unsigned int rows, unsigned int columns);

// Zera todos os elementos de uma matriz
void clearMatrix(double **matrix, unsigned int rows, unsigned int columns);

// Zera todos os elementos de um vetor
void clearArray(double *arr, unsigned int n);

// Imprime uma matriz
void printMatrix(double **matrix, unsigned int rows, unsigned int columns);

// Preenche uma matriz identidade
void initializeIdentityMatrix(double **matrix, unsigned int n);

// Lê uma matriz
void readMatrix(double **matrix, unsigned int rows, unsigned int columns);

void multiplyMatrices(double **A, double **B, double **result, unsigned int n);

void subtractMatrices(double **A, double **B, double **result, unsigned int n);
#endif