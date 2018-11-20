#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int x;
    int y;
    unsigned int gcd;
} eea_result_t;

unsigned int _abs(int z);

unsigned int simple_euclid_alg(int a, int b);

eea_result_t extended_euclid_alg(int a, int b);

int calc_mutiplicative_inverse(int number, unsigned int modulus);
