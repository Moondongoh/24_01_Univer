//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <time.h>
//
//int num;
//
//// ȿ������ �Ҽ� �Ǻ� �Լ�
//int is_prime_simple(long long num) {
//    if (num <= 1) return 0;
//    if (num == 2) return 1;
//    if (num % 2 == 0) return 0;
//    for (long long i = 3; i <= sqrt(num); i += 2) {
//        if (num % i == 0) return 0;
//    }
//    return 1;
//}
//
//// ��ȿ������ �Ҽ� �Ǻ� �Լ�
//int is_prime_complex(long long num) {
//    if (num < 2) return 0;
//    if (num == 2) return 1;
//    if (num % 2 == 0) return 0;
//
//    for (long long i = 3; i <= num / 2; i += 2) {
//        if (num % i == 0) return 0;
//    }
//
//    return 1;
//}
//
//int main() {
//    printf("���� �Է� : ");
//    scanf("%d", &num);
//    printf("�Էµ� ���� : %d\n", num);
//
//    clock_t start, end;
//    double cpu_time_used;
//
//    // ȿ������ �Ҽ� �Ǻ� �Լ��� ���� �ð� ����
//    start = clock();
//    int simple_count = 0;
//    for (long long i = 2; i <= num; i++) {
//        if (is_prime_simple(i)) {
//            simple_count++;
//        }
//    }
//    end = clock();
//    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
//    printf("is_prime_simple �Լ� ���� �ð�: %f ��\n", cpu_time_used);
//    printf("is_prime_simple �Ҽ� ����: %d\n", simple_count);
//
//    // ��ȿ������ �Ҽ� �Ǻ� �Լ��� ���� �ð� ����
//    start = clock();
//    int complex_count = 0;
//    for (long long i = 2; i <= num; i++) {
//        if (is_prime_complex(i)) {
//            complex_count++;
//        }
//    }
//    end = clock();
//    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
//    printf("is_prime_complex �Լ� ���� �ð�: %f ��\n", cpu_time_used);
//    printf("is_prime_complex �Ҽ� ����: %d\n", complex_count);
//
//    return 0;
//}
