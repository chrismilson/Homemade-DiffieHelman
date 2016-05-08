#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long long fastPow(int, int, int);

int main(int argc, char  **argv) {
  int p = 73685062; // large prime
  int q = 3349321;  // large prime that divides p - 1.
  int g = 26794569; // has order q in F*_p.

  int a = 2;
  while (fastPow(a, 22, p) != 1) {
    a++;
  }

  printf("a is %d\n", a);

  return 0;
}

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
