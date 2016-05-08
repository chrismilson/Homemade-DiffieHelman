#include "main.h"

int main(int argc, char  **argv) {
  int p = 73685062; // large prime
  int q = 3349321;  // large prime that divides p - 1.
  int g = 26794569; // has order q in F*_p.
  int encode = 0, decode = 0;

  int privateKey, privFlag = 0; // this is the private key of the person encrypting/decrypting the data
  int publicKey, pubFlag = 0;  // this is the public key of the person that is the desired recipient/sender.

  while ((c = getopt(argc, argv, "edp:P:")) != -1) {
    switch(c) {
      case 'e':
        encode = 1;
        break;
      case 'd':
        decode = 1;
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

  if ((encode && decode) || (!encode && !decode)) {
    fprintf(stderr, "Only one of encode or decode can be chosen at a time.\n");
    return 1;
  }

  if (!privFlag) {
    printf("What is your private key?");
    scanf("\n %d", &privateKey);
  }

  if (!pubFlag) {
    if (encode) {
      printf("What is the public key of the intended recipient?");
      scanf("\n %d", &publicKey);
    } else {
      printf("What is the public key of the sender?");
      scanf("\n %d", &publicKey);
    }
  }



  return 0;
}
