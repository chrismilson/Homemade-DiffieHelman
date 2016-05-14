#include "encode.h"

void encode(char *plaintext, char *cyphertext, int *sharedKey) {
  FILE *ptFile;
  FILE *ctFile;

  ptFile = fopen(plaintext, "rb");
  ctFile = fopen(cyphertext, "wb");

  fseek(ptFile, 0L, SEEK_END);
  int inSize = ftell(ptFile);
  fseek(ptFile, 0L, SEEK_SET);

  Matrix *sharedMatrix;
  sharedMatrix = setBlock(sharedKey);

  Matrix *plain, *cipher;
  int *block;
  block = malloc(sizeof(int) * 4);

  int i, j;
  for (i = 0; i < inSize / 16; i++) {
    for (j = 0; j < 4; j++) {
      block[j] = 0;
      block[j] |= fgetc(ptFile);
      block[j] |= fgetc(ptFile) << 8;
      block[j] |= fgetc(ptFile) << 16;
      block[j] |= fgetc(ptFile) << 24;
    }
    plain = setBlock(block);
    cipher = shiftRows(plain);
    cipher = mixCols(cipher);
    cipher = matrixXOR(sharedMatrix, cipher);
    
    for (j = 0; j < 4; j++) {
      fputc(block[j] & 0xff, ctFile);
      fputc((block[j] >> 8) & 0xff, ctFile);
      fputc((block[j] >> 16) & 0xff, ctFile);
      fputc((block[j] >> 24) & 0xff, ctFile);
    }
  }

  if (!(inSize % 16)) {
    free(block);
    fclose(ptFile); fclose(ctFile);
    return;
  }

  for (i = 0; i < (inSize % 16) / 4; i++) {
    block[i] = 0;
    block[i] |= fgetc(ptFile);
    block[i] |= fgetc(ptFile) << 8;
    block[i] |= fgetc(ptFile) << 16;
    block[i] |= fgetc(ptFile) << 24;
  }

  block[(inSize % 16) / 4] = 0;
  for (i = 0; i < inSize % 4; i++) {
    block[(inSize % 16) / 4] |= fgetc(ptFile) << (8 * (4 - i));
  }

  for (i = inSize % 4; i < inSize % 16; i++) {
    block[(inSize % 16) / 4] |= (rand() % 255) << (8 * (4 - i));
  }

  for (i = (inSize % 16) / 4 + 1; i < 4; i++) {
    block[i] = rand() % 2147483648;
  }

  plain = setBlock(block);
  cipher = shiftRows(plain);
  cipher = mixCols(cipher);
  cipher = matrixXOR(sharedMatrix, cipher);

  block = getBlock(cipher);
  for (j = 0; j < 4; j++) {
    fputc(block[j] & 0xff, ctFile);
    fputc((block[j] >> 8) & 0xff, ctFile);
    fputc((block[j] >> 16) & 0xff, ctFile);
    fputc((block[j] >> 24) & 0xff, ctFile);
  }
  free(block);
  fclose(ptFile); fclose(ctFile);
  return;
}
