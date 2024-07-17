//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>
//#include <time.h>
//#include <math.h>
//
//// ����ü ����
//typedef struct {
//    long long start;
//    long long end;
//    long long step;
//} ThreadArgs;
//
//int count = 0;
//
//// �Ӱ� ���� ���� ����
//CRITICAL_SECTION cs;
//
//// �Ҽ� �Ǻ� �Լ�
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
//// ������ �Լ�
//DWORD WINAPI prime_count(LPVOID lpParam) {
//    ThreadArgs* args = (ThreadArgs*)lpParam;
//
//    // �Ӱ� ���� ����
//    EnterCriticalSection(&cs);
//
//    // �Ҽ� ã��
//    for (long long i = args->start; i <= args->end; i += args->step) {
//        if (is_prime(i)) {
//            count++;
//        }
//    }
//
//    // �Ӱ� ���� ����
//    LeaveCriticalSection(&cs);
//
//    // ������ ����
//    return count;
//}
//
//int main() {
//    int num_threads[] = { 1, 4, 8, 16, 32 };
//    int num = 1000000;
//    HANDLE hThreads[32];
//    DWORD threadIds[32];
//    ThreadArgs args[32];
//    int results[32] = { 0 };
//    clock_t start, end;
//
//    // �Ӱ� ���� �ʱ�ȭ
//    InitializeCriticalSection(&cs);
//
//    // �� ������ ���� ���� �Ҽ� ã�� �� �ð� ����
//    for (int i = 0; i < sizeof(num_threads) / sizeof(num_threads[0]); ++i) {
//        int tnum = num_threads[i];
//        start = clock();
//
//        for (int j = 0; j < tnum; ++j) {
//            args[j].start = j + 1;
//            args[j].end = num;
//            args[j].step = tnum;
//            hThreads[j] = CreateThread(NULL, 0, prime_count, &args[j], 0, &threadIds[j]);
//            if (hThreads[j] == NULL) {
//                printf("Error creating thread %d. Error code: %lu\n", j, GetLastError());
//                return 1;
//            }
//        }
//
//        // �����尡 ��� ����� ������ ���
//        WaitForMultipleObjects(tnum, hThreads, TRUE, INFINITE);
//
//        // �� �������� ��� ���
//        for (int j = 0; j < tnum; ++j) {
//            DWORD exitCode;
//            if (GetExitCodeThread(hThreads[j], &exitCode)) {
//                results[j] = exitCode;
//            }
//            else {
//                printf("Error getting exit code for thread %d. Error code: %lu\n", j, GetLastError());
//            }
//            CloseHandle(hThreads[j]);
//        }
//
//        end = clock();
//        printf("%d ���� ������ Ȱ�� �ð� : %f �� %d��\n", tnum, (double)(end - start) / CLOCKS_PER_SEC, count);
//        count = 0;
//    }
//
//    // �Ӱ� ���� ����
//    DeleteCriticalSection(&cs);
//
//    return 0;
//}
