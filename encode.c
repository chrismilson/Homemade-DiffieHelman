#include "encode.h"

void encode(char *plaintext, char *cyphertext, int sharedKey) {
  FILE *ptFile;
  FILE *ctFile;

  ptFile = fopen(plaintext, "rb");
  ctFile = fopen(cyphertext, "wb");

  

  fclose(ptFile); fclose(ctFile);
  return;
}
