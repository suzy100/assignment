// 2017029752_¹é½Â¼ö_12525

#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>
#include <stdio.h>

using namespace std;

void print_LCS(string X, int i, int j);

// char A[501], B[501];
string A, B;
char b[501][501];
int c[501][501];

int main(void) {

	cin >> A >> B;
	// scanf("%s", &A);
	// fgets(A, sizeof(A), stdin);
	// A[strlen(A) - 1] = '\0';

	// scanf("%s", &B);
	// fgets(B, sizeof(B), stdin);
	// B[strlen(B) - 1] = '\0';

	if (A < B) {
		swap(A, B);
	}

	int m = (int)A.length();
	int n = (int)B.length();


	// char** b = new char*[m+1];
	// (int i = 1; i <= m; i++) {
	// 	b[i] = new char[n + 1];
	// }

	// int** c = new int*[m+1];
	// for (int i = 0; i <= m; i++) {
	//	c[i] = new int[n + 1];
	// } 


	// for (int i = 1; i <= m; i++) {
	//	c[i][0] = 0;
	// }
	// for (int j = 0; j <= n; j++) {
	// 	c[0][j] = 0;
	// }

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (A[i - 1] == B[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 'q';
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = 'w';
			}
			else {
				c[i][j] = c[i][j - 1];
				b[i][j] = 'a';
			}
		}
	}

	// printf("%d\n", c[m][n]);
	print_LCS(A.c_str(), m, n);

	return 0;

}

void print_LCS(string X, int i, int j) {

	if (i == 0 || j == 0) return;
	
	if (b[i][j] == 'q') {
		print_LCS(X, i - 1, j - 1);
		printf("%c", X[i - 1]);
	}
	else if (b[i][j] == 'w') {
		print_LCS(X, i - 1, j);
	}
	else {
		print_LCS(X, i, j - 1);
	}

}