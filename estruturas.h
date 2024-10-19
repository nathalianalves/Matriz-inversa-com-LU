/*  Biblioteca de funções relacionadas às estruturas utilizadas: matrizes e vetores
    Nathália Nogueira Alves - GRR20232349 - UFPR
*/

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

// Lê uma matriz rows x columns
void readMatrix(double **matrix, unsigned int rows, unsigned int columns);

// Multiplica as matrizes A e B e guarda o resultado em result
void multiplyMatrices(double **A, double **B, double **result, unsigned int n);

// Calcula A - B e guarda em result
void subtractMatrices(double **A, double **B, double **result, unsigned int n);

#endif