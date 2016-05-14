#ifndef CRYPTO_H

#define CRYPTO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "encode.h"
#include "decode.h"

long long fastPow(int, int, int);

int generateNewKey(int);

#endif
