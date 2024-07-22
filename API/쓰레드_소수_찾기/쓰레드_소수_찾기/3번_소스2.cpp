//#include <windows.h>
//#include <tchar.h>
//#include <stdio.h>
//#include <time.h>
//
//typedef struct tmp {
//    DWORD start;
//    DWORD end;
//} tp;
//
//DWORD WINAPI prime(LPVOID param) {
//    tp* range = (tp*)param; // LPVOID�� tp*�� ��ȯ
//    int count = 0;
//    for (DWORD i = range->start; i < range->end; i++) {
//        if (i < 2) continue;
//        bool isPrime = true;
//        for (DWORD j = 2; j <= i / 2; j++) {
//            if (i % j == 0) {
//                isPrime = false;
//                break;
//            }
//        }
//        if (isPrime) {
//            count++;
//        }
//    }
//    return count;
//}
//
//int makethread(HANDLE* hThreads, DWORD* threadIds, DWORD tnum, tp* param, int* results) {
//    clock_t start, end;
//    start = clock();
//    for (DWORD i = 0; i < tnum; i++) {
//        hThreads[i] = CreateThread(
//            NULL,               // �⺻ ���� �Ӽ�
//            0,                  // �⺻ ���� ũ��
//            prime,              // ������ �Լ�
//            &param[i],          // ������ �Լ��� ������ �Ű� ����
//            0,                  // �⺻ ���� �÷���
//            &threadIds[i]       // ������ ID�� ���� ������
//        );
//
//        if (hThreads[i] == NULL) {
//            _tprintf(_T("Error creating thread %d. Error code: %lu\n"), i, GetLastError());
//            return 1;
//        }
//    }
//
//    // ��� �����尡 ����� ������ ���
//    WaitForMultipleObjects(tnum, hThreads, TRUE, INFINITE);
//
//    // �� �������� ���� �ڵ� ���
//    for (DWORD i = 0; i < tnum; i++) {
//        DWORD exitCode;
//        if (GetExitCodeThread(hThreads[i], &exitCode)) {
//            results[i] = exitCode;
//        }
//        else {
//            _tprintf(_T("Error getting exit code for thread %d. Error code: %lu\n"), i, GetLastError());
//        }
//        CloseHandle(hThreads[i]);
//    }
//    end = clock();
//    printf("%d ���� ������ Ȱ�� �ð� : %f \n", tnum, (float)(end - start) / CLOCKS_PER_SEC);
//    return 0;
//}
//
//int _tmain() {
//    HANDLE hThreads[32];
//    DWORD threadIds[32];
//    int results[32] = { 0 };
//
//    const DWORD RANGE_END = 1000000;
//
//    for (int tnum = 1; tnum <= 32; tnum *= 2) {
//        tp* tParams = (tp*)malloc(sizeof(tp) * tnum);
//        DWORD rangeSize = RANGE_END / tnum;
//
//        for (DWORD i = 0; i < tnum; i++) {
//            tParams[i].start = i * rangeSize;
//            tParams[i].end = (i == tnum - 1) ? RANGE_END : tParams[i].start + rangeSize;
//        }
//
//        makethread(hThreads, threadIds, tnum, tParams, results);
//
//        int totalPrimes = 0;
//        for (DWORD i = 0; i < tnum; i++) {
//            totalPrimes += results[i];
//        }
//        printf("Total prime numbers found with %d threads: %d\n", tnum, totalPrimes);
//
//        free(tParams);
//    }
//
//    return 0;
//}
