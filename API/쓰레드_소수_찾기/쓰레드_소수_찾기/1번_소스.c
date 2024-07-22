//#include <windows.h>
//#include <stdio.h>
//#include <time.h>
//#include <math.h>
//
//typedef struct {
//    DWORD end;
//    DWORD start;
//    DWORD step;
//} ThreadArgs;
//
//volatile LONG total_prime_count = 0; // ���� ����
//
//// �Ҽ� ���θ� �Ǻ��ϴ� �Լ�
//int is_prime(long long num) {
//    if (num <= 1) return 0;
//    if (num == 2) return 1;
//    if (num % 2 == 0) return 0;
//    for (long long i = 3; i <= sqrt(num); i += 2) {
//        if (num % i == 0) return 0;
//    }
//    return 1;
//}
//
//// �� �����忡�� ������ �Լ�
//DWORD WINAPI prime_count(LPVOID param) {
//    ThreadArgs* args = (ThreadArgs*)param;
//    int count = 0;
//    for (DWORD i = args->start; i <= args->end; i += args->step) {
//        if (is_prime(i)) {
//            count++;
//        }
//    }
//    InterlockedAdd(&total_prime_count, count); // ���� ������ ����
//    return 0;
//}
//
//int main() {
//    const long long n = 1000000; // ������ ����
//    int thread_counts[] = { 1, 4, 8, 16, 32 }; // ������ ���� �迭
//    int num_configs = sizeof(thread_counts) / sizeof(thread_counts[0]); // �迭 ����
//    HANDLE hThreads[32];
//    DWORD threadIds[32];
//    ThreadArgs args[32];
//
//    for (int i = 0; i < num_configs; i++) {
//        int num_threads = thread_counts[i]; // ���� ������ ������ ����
//        clock_t start, end;
//        start = clock();
//        total_prime_count = 0; // �ʱ�ȭ
//
//        for (int t = 0; t < num_threads; t++) {
//            args[t].start = t + 1;
//            args[t].end = n;
//            args[t].step = num_threads;
//            hThreads[t] = CreateThread(NULL, 0, prime_count, &args[t], 0, &threadIds[t]);
//            if (hThreads[t] == NULL) {
//                printf("������ %d ���� �� ���� �߻�. ���� �ڵ�: %lu\n", t, GetLastError());
//                return 1;
//            }
//        }
//
//        // ��� �������� �ϷḦ ���
//        WaitForMultipleObjects(num_threads, hThreads, TRUE, INFINITE);
//
//        // ������ �ڵ��� ����
//        for (int t = 0; t < num_threads; t++) {
//            CloseHandle(hThreads[t]);
//        }
//
//        end = clock();
//        double total_time = (double)(end - start) / CLOCKS_PER_SEC;
//        printf("������ ����: %d, �ҿ� �ð�: %f ��, ã�� �Ҽ� ����: %ld\n", num_threads, total_time, total_prime_count);
//    }
//
//    return 0;
//}
