#include "eea.h"

/**
 * Calculates and prints the calculation of gcd(a,b) using the euclidean algorithmn.
 * Returns gcd(a,b)
 */
unsigned int simple_euclid_alg(int a, int b) {
    // Get the larger and smaller value and save their absolutes.
    unsigned int _max = _abs((a > b ? a : b));
    unsigned int _min = _abs((a < b ? a : b));

    unsigned int q = _max / _min;
    unsigned int r = _max % _min;

    printf("%d = %d * %d + %d\n", _max, q, _min, r);
    while (r != 0) {
        _max = _min;
        _min = r;
        q = _max / _min;
        r = _max % _min;
        printf("%d = %d * %d + %d\n", _max, q, _min, r);
    }

    return q;
}

eea_result_t extended_euclid_alg(int a, int b) {
    int old_s, s;
    int old_t, t;
    int old_r, r;
    int tmp;
    a = _abs(a);
    b = _abs(b);
    old_s = 1, s = 0;
    old_t = 0; t = 1;
    old_r = a; r = b;

    while (r != 0) {
        int q = old_r / r;

        tmp = r;
        r = old_r - q * r;
        old_r = tmp;

        tmp = s;
        s = old_s - q * s;
        old_s = tmp;

        tmp = t;
        t = old_t - q * t;
        old_t = tmp;
    }

    eea_result_t res;
    res.gcd = old_r;
    res.x = old_s;
    res.y = old_t;

    printf("gcd(%d,%d) = %5d * %-d + %5d * %-d = %d\n",a,b, res.x, a, res.y, b, res.gcd);
    return res;

}

unsigned int _abs(int z) {
    return (z < 0 ? -z : z);
}

int main(int argc, char** argv) {
    simple_euclid_alg(atoi(argv[1]), atoi(argv[2]));
    extended_euclid_alg(atoi(argv[1]), atoi(argv[2]));
}
