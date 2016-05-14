#include "decode.h"

void decode(char *ciphertext, char *plaintext, int *sharedKey) {
  FILE *ctFile;
  FILE *ptFile;

  ctFile = fopen(ciphertext, "rb");
  ptFile = fopen(plaintext, "wb");

  fseek(ctFile, 0L, SEEK_END);
  int inSize = ftell(ctFile);
  fseek(ctFile, 0L, SEEK_SET);

  Matrix *sharedMatrix;
  sharedMatrix = setBlock(sharedKey);

  int i, j;
  for (i = 0; i < inSize / 16; i++) {
    int *block;
    block = malloc(sizeof(int) * 4);
    for (j = 0; j < 4; j++) {
      block[j] = 0;
      block[j] |= fgetc(ctFile);
      block[j] |= fgetc(ctFile) << 8;
      block[j] |= fgetc(ctFile) << 16;
      block[j] |= fgetc(ctFile) << 24;
    }
    Matrix *cipher, *plain;
    cipher = setBlock(block);

    plain = unshiftRows(matrixXOR(sharedMatrix, cipher));
    block = getBlock(plain);
    for (j = 0; j < 4; j++) {
      fputc(block[j] & 0xff, ptFile);
      fputc((block[j] >> 8) & 0xff, ptFile);
      fputc((block[j] >> 16) & 0xff, ptFile);
      fputc((block[j] >> 24) & 0xff, ptFile);
    }
    free(block);
  }

  fclose(ctFile); fclose(ctFile);
  return;
}
