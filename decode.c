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

  int *block;
  block = malloc(sizeof(int) * 4);
  Matrix *cipher, *plain;

  int i, j;
  for (i = 0; i < inSize / 16 - 1; i++) {
    for (j = 0; j < 4; j++) {
      block[j] = 0;
      block[j] |= fgetc(ctFile);
      block[j] |= fgetc(ctFile) << 8;
      block[j] |= fgetc(ctFile) << 16;
      block[j] |= fgetc(ctFile) << 24;
    }
    cipher = setBlock(block);
    plain = matrixXOR(sharedMatrix, cipher);
    plain = unshiftRows(plain);

    block = getBlock(plain);
    for (j = 0; j < 4; j++) {
      fputc(block[j] & 0xff, ptFile);
      fputc((block[j] >> 8) & 0xff, ptFile);
      fputc((block[j] >> 16) & 0xff, ptFile);
      fputc((block[j] >> 24) & 0xff, ptFile);
    }
  }

  for (j = 0; j < 4; j++) {
    block[j] = 0;
    block[j] |= fgetc(ctFile);
    block[j] |= fgetc(ctFile) << 8;
    block[j] |= fgetc(ctFile) << 16;
    block[j] |= fgetc(ctFile) << 24;
  }
  cipher = setBlock(block);
  plain = matrixXOR(sharedMatrix, cipher);
  plain = unshiftRows(plain);

  block = getBlock(plain);
  char ch;
  for (j = 0; j < 4; j++) {
    for (i = 0; i < 4; i++) {
      if ((ch = (block[j] >> (i * 8)) & 0xff) == EOF) {
        free(block);
        fclose(ctFile); fclose(ptFile);
        return;
      }
      fputc(ch, ptFile);
    }
  }

  free(block);
  fclose(ctFile); fclose(ptFile);
  return;
}
