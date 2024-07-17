#include <stdio.h>
#include <omp.h>
#include <math.h>

// 소수 판별 함수
int is_prime(long long num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (long long i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    const long long n = 1000000;
    int total_prime_count_atomic, total_prime_count_critical;
    double start_time, end_time;
    int thread_counts[] = { 1, 4, 8, 16, 32 };
    int num_configs = sizeof(thread_counts) / sizeof(thread_counts[0]);
    const int chunk_size = 100;

    for (int i = 0; i < num_configs; i++) {
        int num_threads = thread_counts[i];

        // 첫 번째 방법: #pragma omp atomic
        total_prime_count_atomic = 0;
        start_time = omp_get_wtime();
#pragma omp parallel num_threads(num_threads)
        {
            int local_prime_count = 0;
#pragma omp for schedule(dynamic, chunk_size)
            for (long long j = 1; j <= n; j++) {
                if (is_prime(j)) {
                    local_prime_count++;
                }
            }
#pragma omp atomic
            total_prime_count_atomic += local_prime_count;
        }
        end_time = omp_get_wtime();
        printf("Atomic - Threads: %d, Prime Count Time: %f seconds, Primes: %d\n", num_threads, end_time - start_time, total_prime_count_atomic);

        // 두 번째 방법: #pragma omp critical
        int global_prime_count = 0;
        start_time = omp_get_wtime();
#pragma omp parallel num_threads(num_threads)
        {
            int local_prime_count = 0;
#pragma omp for schedule(dynamic, chunk_size)
            for (long long j = 1; j <= n; j++) {
                if (is_prime(j)) {
                    local_prime_count++;
                }
            }
            // 전역 변수에 접근할 때 임계 구역 사용
#pragma omp critical
            {
                global_prime_count += local_prime_count;
            }
        }
        end_time = omp_get_wtime();
        printf("Critical - Threads: %d, Prime Count Time: %f seconds, Primes: %d\n\n", num_threads, end_time - start_time, global_prime_count);
    }

    return 0;
}
