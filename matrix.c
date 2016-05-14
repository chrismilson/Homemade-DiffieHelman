#include "matrix.h"

Matrix *newMatrix(int r, int c) {
  Matrix *dest;
  dest = malloc(sizeof(int) * (r * c + 2));
  dest->rows = r;
  dest->cols = c;
  dest->entries = malloc(sizeof(int) * r * c);
  memset(dest->entries, 0, sizeof(int) * r * c);
  return dest;
} // initialises a zero matrix of a set size.

int get(int x, int y, Matrix *a) {
  if (x < a->rows && y < a->cols && x >= 0 && y >= 0) {
    return a->entries[(x) + (y) * a->cols];
  } else {
    return NAN;
  }
}

int set(int val, int x, int y, Matrix *a) {
  if (x < a->rows && y < a->cols && x >= 0 && y >= 0) {
    a->entries[(x) + (y) * a->cols] = val;
    return 0;
  } else {
    return 1;
  }
}

Matrix *matrixProduct(Matrix *a, Matrix *b) {
  int aRows = a->rows, aCols = b->cols;
  if (a->cols == b->rows) {
    Matrix *answer;
    answer = newMatrix(aRows, aCols);
    int i, j, p;
    for (i = 0; i < aRows; i++) {
      for (j = 0; j < aCols; j++) {
        int sum = 0;
        for (p = 0; p < aRows; p++) {
          sum += a->entries[i + p * a->cols] * b->entries[p + j * a->cols];
        }
        answer->entries[i + j * a->cols] = sum;
      }
    }
    return answer;
  } else {
    return NULL;
  }
}

Matrix *scalarProduct(int s, Matrix *a) {
  Matrix *result;
  result = newMatrix(a->rows, a->cols);
  int i, j;
  for (i = 0; i < a->rows; i++) {
    for (j = 0; j < a->cols; j++) {
      result->entries[i + j * a->rows] = s * a->entries[i + j * a->rows];
    }
  }
  return result;
}

Matrix *scalarQuotient(int s, Matrix *a) {
  Matrix *result;
  result = newMatrix(a->rows, a->cols);
  int i, j;
  for (i = 0; i < a->rows; i++) {
    for (j = 0; j < a->cols; j++) {
      result->entries[i + j * a->rows] = a->entries[i + j * a->rows] / s;
    }
  }
  return result;
}

void matrixPrint(Matrix *matrix) {
  int i, j;
  for (i = 0; i < matrix->cols; i++) {
    for (j = 0; j < matrix->rows; j++) {
      printf("%d\t", matrix->entries[i + j * matrix->cols]);
    }
    printf("\n");
  }
  printf("\n");
  return;
}

// The following functions are specifically for use with AES (advanced
// encryption standard).
Matrix *setBlock(int val[4]) {
  int i, j;
  Matrix *block;
  block = newMatrix(4, 4);
  for (i = 0; i < 4; i++) {
    block->entries[i] = (val[i] >> 24) & 0xff;
    block->entries[i + 4] = (val[i] >> 16) & 0xff;
    block->entries[i + 8] = (val[i] >> 8) & 0xff;
    block->entries[i + 12] = val[i] & 0xff;
  }
  return block;
}

int *getBlock(Matrix *matrix) {
  int i, j;
  int *val;
  val = malloc(sizeof(int) * 4);
  memset(val, 0, sizeof(int) * 4);

  if (matrix->rows == 4 || matrix->cols == 4) {
    for (i = 0; i < 4; i++) {
      val[i] = (matrix->entries[i] << 24) | (matrix->entries[i + 4] << 16) |
        (matrix->entries[i + 8] << 8) |
        (matrix->entries[i + 12]);
    }
  }

  return val;
}

Matrix *shiftRows(Matrix *matrix) {
  int i, j;
  Matrix *result;
  result = newMatrix(4, 4);
  if (matrix->rows == 4 || matrix->cols == 4) {
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
        result->entries[j + i * 4] = matrix->entries[j + ((i + j) % 4) * 4];
      }
    }
    return result;
  }
  return NULL;
}

Matrix *unshiftRows(Matrix *matrix) {
  int i, j;
  Matrix *result;
  result = newMatrix(4, 4);
  if (matrix->rows == 4 || matrix->cols == 4) {
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
        result->entries[j + i * 4] = matrix->entries[j + ((i + (4 - j)) % 4) * 4];
      }
    }
    return result;
  }
  return NULL;
}

Matrix *shiftCols(Matrix *matrix) {
  int i, j;
  Matrix *result;
  result = newMatrix(4, 4);
  if (matrix->rows == 4 || matrix->cols == 4) {
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
        result->entries[i + j * 4] = matrix->entries[((i + j) % 4) + j * 4];
      }
    }
    return result;
  }
  return NULL;
}

Matrix *unshiftCols(Matrix *matrix) {
  int i, j;
  Matrix *result;
  result = newMatrix(4, 4);
  if (matrix->rows == 4 && matrix->cols == 4) {
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
        result->entries[i + j * 4] = matrix->entries[((i + (4 - j)) % 4) + j * 4];
      }
    }
    return result;
  }
  return NULL;
}

Matrix *mixCols(Matrix *matrix) {
  if (matrix->rows != 4 || matrix->cols != 4) {
    return NULL;
  }

  int *mixer;
  mixer = malloc(sizeof(int) * 4);
  mixer[0] = 33620227;
  mixer[1] = 50462977;
  mixer[2] = 16974337;
  mixer[3] = 16843522;

  Matrix *result;

  result = matrixProduct(setBlock(mixer), matrix);
  free(mixer);
  return result;
}

Matrix *unmixCols(Matrix *matrix) {
  if (matrix->rows != 4 || matrix->cols != 4) {
    return NULL;
  }

  Matrix *unmixer, *result;
  unmixer = newMatrix(4, 4);
  unmixer->entries[0] = -4;
  unmixer->entries[1] = 3;
  unmixer->entries[2] = -11;
  unmixer->entries[3] = 17;
  unmixer->entries[4] = 17;
  unmixer->entries[5] = -4;
  unmixer->entries[6] = 3;
  unmixer->entries[7] = -11;
  unmixer->entries[8] = -11;
  unmixer->entries[9] = 17;
  unmixer->entries[10] = -4;
  unmixer->entries[11] = 3;
  unmixer->entries[12] = 3;
  unmixer->entries[13] = -11;
  unmixer->entries[14] = 17;
  unmixer->entries[15] = -4;

  result = matrixProduct(unmixer, matrix);
  result = scalarQuotient(35, result);
  return result;
}

Matrix *matrixXOR(Matrix *a, Matrix *b) {
  if (a->rows == b->rows && a->cols == b->cols) {
    int rows = a->rows, cols = a->cols, i, j;
    Matrix *result;
    result = newMatrix(rows, cols);

    for (i = 0; i < rows; i++) {
      for (j = 0; j < cols; j++) {
        result->entries[i + j * rows] = a->entries[i + j * rows] ^
          b->entries[i + j * rows];
      }
    }
    return result;
  }
  return NULL;
}
