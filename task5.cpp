#include <omp.h>
#include <cstdio>

const int cutoff = 20;

long fib_seq(int n) {
    if (n < 2) return n;
    return fib_seq(n - 1) + fib_seq(n - 2);
}

long fib(int n) {
    if (n <= cutoff) return fib_seq(n);
    long x, y;
    #pragma omp task shared(x)
    x = fib(n - 1);
    #pragma omp task shared(y)
    y = fib(n - 2);
    #pragma omp taskwait
    return x + y;
}

int main() {
    const int n = 38;
    long result = 0;

    double t = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }
    t = omp_get_wtime() - t;

    printf("%ld\n%f\n", result, t);
}
