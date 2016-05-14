#ifndef MATRIX_H

#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct Matrix {
  int rows;
  int cols;
  int *entries;
} Matrix;

Matrix *newMatrix(int, int);

int get(int, int, Matrix*);

int set(int, int, int, Matrix*);

Matrix *matrixProduct(Matrix*, Matrix*);

Matrix *scalarProduct(int, Matrix*);

Matrix *scalarQuotient(int, Matrix*);

void matrixPrint(Matrix*);

Matrix *setBlock(int[4]);

int *getBlock(Matrix*);

Matrix *shiftRows(Matrix*);

Matrix *unshiftRows(Matrix*);

Matrix *shiftCols(Matrix*);

Matrix *unshiftCols(Matrix*);

Matrix *mixCols(Matrix*);

Matrix *unmixCols(Matrix *matrix);

Matrix *matrixXOR(Matrix*, Matrix*);

#endif
