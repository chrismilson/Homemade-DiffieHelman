#include "main.h"

long long fastPow(int a, int n, int m) {
  long long answer = 1;
  long long expo = n;
  long long base = a;
  while(expo > 0) {
      if (expo & 1) {
        answer *= base;
        answer %= m;
      }
      base *= base;
      base %= m;
      expo >>= 1;
  }
  return answer;
}

int main(int argc, char  **argv) {
  int p = 77807857; // large prime
  int g = 73892587; // another large prime less than p
  int encodeFlag = 0, decodeFlag = 0;

  int privateKey[4], privFlag = 0; // this is the private key of the person encrypting/decrypting the data.
  int publicKey[4], pubFlag = 0;  // this is the public key of the person that is the desired recipient/sender.
  int sharedKey[4];

  int c;
  while ((c = getopt(argc, argv, "ed")) != -1) {
    switch(c) {
      case 'e':
        encodeFlag = 1;
        break;
      case 'd':
        decodeFlag = 1;
        break;
      default:
        break;
    }
  }

  if ((encodeFlag && decodeFlag) || (!encodeFlag && !decodeFlag)) {
    fprintf(stderr, "Only one of encode or decode can be chosen at a time.\n");
    return 1;
  }

  if (!privFlag) {
    printf("What is your private key? ");
    scanf("%d %d %d %d", privateKey, privateKey + 1,
      privateKey + 2, privateKey + 3);
  }

  if (!pubFlag) {
    if (encodeFlag) {
      printf("What is the public key of the intended recipient? ");
      scanf("\n %d %d %d %d", publicKey, publicKey + 1,
        publicKey + 2, publicKey + 3);
    } else {
      printf("What is the public key of the sender? ");
      scanf("\n %d %d %d %d", publicKey, publicKey + 1,
        publicKey + 2, publicKey + 3);
    }
  }

  int i;
  for (i = 0; i < 4; i++) {
    sharedKey[i] = (int) fastPow(publicKey[i], privateKey[i], p);
  }

  encode("test/pt.txt", "test/ct.txt", sharedKey);

  return 0;
}
