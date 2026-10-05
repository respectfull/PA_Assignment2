#include <omp.h>
#include <cstdio>
#include <vector>

int main() {
    const long n = 20000000;
    std::vector<double> a(n), b(n), c(n);
    for (long i = 0; i < n; i++) {
        a[i] = i * 0.5;
        b[i] = i * 1.5;
    }

    double t = omp_get_wtime();
    for (long i = 0; i < n; i++) c[i] = a[i] + b[i];
    double seq = omp_get_wtime() - t;

    t = omp_get_wtime();
    #pragma omp parallel for
    for (long i = 0; i < n; i++) c[i] = a[i] + b[i];
    double par = omp_get_wtime() - t;

    for (long i = 0; i < 5; i++) printf("%.1f ", c[i]);
    printf("... ");
    for (long i = n - 5; i < n; i++) printf("%.1f ", c[i]);
    printf("\n%f %f %.2f\n", seq, par, seq / par);
}
