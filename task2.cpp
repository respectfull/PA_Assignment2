#include <omp.h>
#include <cmath>
#include <cstdio>

int main() {
    const long n = 500000000;
    const double h = 1.0 / n;
    double sum = 0.0;

    double t = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < n; i++) {
        double x = (i + 0.5) * h;
        sum += 4.0 / (1.0 + x * x);
    }
    double pi = sum * h;
    t = omp_get_wtime() - t;

    printf("%.12f\n%.3e\n%f\n", pi, std::fabs(pi - M_PI), t);
}
