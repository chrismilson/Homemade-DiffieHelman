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

  int i, j;
  for (i = 0; i < inSize / 16; i++) {
    int *block;
    block = malloc(sizeof(int) * 4);
    for (j = 0; j < 4; j++) {
      block[j] = 0;
      block[j] |= fgetc(ptFile);
      block[j] |= fgetc(ptFile) << 8;
      block[j] |= fgetc(ptFile) << 16;
      block[j] |= fgetc(ptFile) << 24;
    }
    Matrix *plain, *cipher;
    plain = setBlock(block);

    cipher = matrixXOR(sharedMatrix, shiftRows(plain));
    block = getBlock(cipher);
    for (j = 0; j < 4; j++) {
      fputc(block[j] & 0xff, ctFile);
      fputc((block[j] >> 8) & 0xff, ctFile);
      fputc((block[j] >> 16) & 0xff, ctFile);
      fputc((block[j] >> 24) & 0xff, ctFile);
    }
    free(block);
  }

  fclose(ptFile); fclose(ctFile);
  return;
}
