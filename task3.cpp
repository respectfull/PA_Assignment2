#include <omp.h>
#include <cstdio>

bool is_prime(long x) {
    if (x < 2) return false;
    if (x % 2 == 0) return x == 2;
    for (long d = 3; d * d <= x; d += 2)
        if (x % d == 0) return false;
    return true;
}

int main() {
    const long n = 5000000;
    long count = 0;

    double t = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, 1000)
    for (long i = 2; i <= n; i++) {
        if (is_prime(i)) {
            #pragma omp atomic
            count++;
        }
    }
    t = omp_get_wtime() - t;

    printf("%ld\n%f\n", count, t);
}
