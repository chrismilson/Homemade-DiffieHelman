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

  int privateKey, privFlag = 0; // this is the private key of the person encrypting/decrypting the data.
  int publicKey, pubFlag = 0;  // this is the public key of the person that is the desired recipient/sender.
  long sharedKey;

  int c;
  while ((c = getopt(argc, argv, "edp:P:")) != -1) {
    switch(c) {
      case 'e':
        encodeFlag = 1;
        break;
      case 'd':
        decodeFlag = 1;
        break;
      case 'p':
        privFlag = 1;
        privateKey = strtol(optarg, NULL, 10);
        break;
      case 'P':
        pubFlag = 1;
        publicKey = strtol(optarg, NULL, 10);
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
    scanf("\n %d", &privateKey);
  }

  if (!pubFlag) {
    if (encodeFlag) {
      printf("What is the public key of the intended recipient? ");
      scanf("\n %d", &publicKey);
    } else {
      printf("What is the public key of the sender? ");
      scanf("\n %d", &publicKey);
    }
  }

  sharedKey = fastPow(publicKey, privateKey, p);

  encode("cyphertext.txt", "output.txt", sharedKey);
  // encode("test.txt", "cyphertext.txt", sharedKey);

  return 0;
}
