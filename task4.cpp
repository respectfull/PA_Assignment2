#include <omp.h>
#include <cstdio>
#include <random>
#include <vector>

int main() {
    const long n = 200000000;
    std::vector<long> counts(omp_get_max_threads(), 0);
    double pi = 0.0;

    double t = omp_get_wtime();
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        std::mt19937_64 gen(12345 + id);
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        long local = 0;

        #pragma omp for nowait
        for (long i = 0; i < n; i++) {
            double x = dist(gen);
            double y = dist(gen);
            if (x * x + y * y <= 1.0) local++;
        }
        counts[id] = local;

        #pragma omp barrier

        #pragma omp single
        {
            long total = 0;
            for (long c : counts) total += c;
            pi = 4.0 * total / n;
        }
    }
    t = omp_get_wtime() - t;

    printf("%.6f\n%ld\n%f\n", pi, n, t);
}
