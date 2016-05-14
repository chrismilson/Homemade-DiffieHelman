#include "encode.h"

void encode(char *plaintext, char *cyphertext, int *sharedKey) {
  FILE *ptFile;
  FILE *ctFile;

  ptFile = fopen(plaintext, "rb");
  ctFile = fopen(cyphertext, "wb");

  fseek(ptFile, 0L, SEEK_END);
  int inSize = ftell(ptFile);
  fseek(ptFile, 0L, SEEK_SET);

  int i, j;
  for (i = 0; i < inSize / 16; i++) {
    int block[4] = {0, 0, 0, 0};
    for (j = 0; j < 4; j++) {
      block[j] |= fgetc(ptFile);
      block[j] |= fgetc(ptFile) << 8;
      block[j] |= fgetc(ptFile) << 16;
      block[j] |= fgetc(ptFile) << 24;
    }
    Matrix *plain, *cipher;
    plain = setBlock(block);
    matrixPrint(plain);
  }

  fclose(ptFile); fclose(ctFile);
  return;
}
