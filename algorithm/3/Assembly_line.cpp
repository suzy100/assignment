// 2017029752_¿¿¿_12525

#include <stdio.h>

int main() {
	int N, e1, e2, x1, x2;
	int** a = new int*[3];
	int** t = new int*[3];

	scanf("%d", &N);

	for (int i = 0; i < 3; i++) {
		a[i] = new int[N + 1];
	}
	for (int i = 0; i <= 3; i++) {
		t[i] = new int[N];
	}

	scanf("%d %d", &e1, &e2);

	scanf("%d %d", &x1, &x2);

	for (int i = 1; i <= N; i++) {
		scanf("%d", &a[1][i]);
	}

	for (int i = 1; i <= N; i++) {
		scanf("%d", &a[2][i]);
	}

	for (int i = 1; i < N; i++) {
		scanf("%d", &t[1][i]);
	}

	for (int i = 1; i < N; i++) {
		scanf("%d", &t[2][i]);
	}

	int** r = new int*[3];
	for (int i = 0; i < 3; i++) {
		r[i] = new int[N + 1];
	}

	int** l = new int*[3];
	for (int i = 0; i < 3; i++) {
		l[i] = new int[N + 1];
	}

	//find Fastest-way
	r[1][1] = e1 + a[1][1];
	r[2][1] = e2 + a[2][1];

	for (int i = 2; i < N+1; i++) {
		if (r[1][i - 1] + a[1][i] <= r[2][i - 1] + t[2][i - 1] + a[1][i]) {
			r[1][i] = r[1][i - 1] + a[1][i];
			l[1][i] = 1;
		}
		else {
			r[1][i] = r[2][i - 1] + t[2][i - 1] + a[1][i];
			l[1][i] = 2;
		}

		if (r[2][i - 1] + a[2][i] < r[1][i - 1] + t[1][i - 1] + a[2][i]) {
			r[2][i] = r[2][i - 1] + a[2][i];
			l[2][i] = 2;
		}
		else {
			r[2][i] = r[1][i - 1] + t[1][i - 1] + a[2][i];
			l[2][i] = 1;
		}
	}

	if (r[1][N] + x1 <= r[2][N] + x2) {
		r[0][0] = r[1][N] + x1;
		l[0][0] = 1;
	}
	else {
		r[0][0] = r[2][N] + x2;
		l[0][0] = 2;
	}

	printf("%d\n", r[0][0]);

	int i = l[0][0];
	int q = N - 2;
	int* result = new int[N];
	result[N - 1] = i;
	for (int j = N; j > 1; j--) {
		i = l[i][j];
		result[q] = i;
		q--;
	}
	
	for (int h = 0; h < N; h++) {
		printf("%d %d\n", result[h], h + 1);
	}
	return 0;
}
