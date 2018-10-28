#include "prime.h"

int isPrime(unsigned int i)
{
    unsigned j;

    if (i < 2)
        return 0;

    for (j = 2; (j * j) <= i; ++j)
        if (!(i % j))
            return 0;

    return 1;
}

