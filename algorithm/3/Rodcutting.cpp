// 2017029752_백승수_12525

#include <stdio.h>

int cutRod(int* arr, int N);

int main() {
        int N;
        scanf("%d", &N);

        int* p = new int[N+1];
        for (int i=1; i<=N; i++) {
                scanf("%d", &p[i]);
        }

        cutRod(p, N);

        return 0;
}

int cutRod(int* p, int N) {
        int* r = new int[N+1];
        int* s = new int[N+1];
        int q;

        r[0] = 0;

        for (int j=1; j<=N; j++) {
                q = 0;
                for (int i=1; i<=j; i++) {
                        if (q < p[i] + r[j-i]) {
                                q = p[i] + r[j-i];
                                s[j] = i;
                        }
                }
                r[j] = q;
        }

        printf("%d\n", q);
        while (N > 0) {
                printf("%d ", s[N]);
                N = N - s[N];
        }
}
