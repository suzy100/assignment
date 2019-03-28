// 2017029752_백승수_12525

 

#define _CRT_SECURE_NO_WARNINGS

 

#include <stdio.h>

 

int main() {

          int N, M, K;

          scanf("%d %d %d", &N, &M, &K);

         

          int* A = new int[K];

          int* B = new int[K];

          int* keys = new int[N];

          int result = 0; 

          for (int i = 0; i < K; i++) {

                    scanf("%d %d", &A[i], &B[i]);

          }

         

          for (int i = 0; i < N; i++) {

                    scanf("%d", &keys[i]);

                    if (keys[i] > M) return -1;

          }

          int* C = new int[M+1];

          for (int i = 0; i <= M; i++) {

                    C[i] = 0;

          }

         

          for (int i = 0; i < N; i++) {

                    C[keys[i]] = C[keys[i]] + 1;

          }

 

          for (int i = 1; i <= M; i++) {

                    C[i] = C[i] + C[i - 1];

          }

 

          for (int i = 0; i < K; i++) {

                    result =  C[B[i]] - C[A[i]-1];
                    printf("%d\n", result);

          }

          return 0;

}
