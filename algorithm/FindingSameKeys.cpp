// 2017029752_¹é½Â¼ö_12525

#include <stdio.h>
#include <map>
using namespace std;

map<int, int> hashtable;

int main(void) {

	int N, M, cnt=0;
	scanf("%d %d", &N, &M);
	
	int* A = new int[N];
	int* B = new int[M];

	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
		hashtable.insert(make_pair(A[i], 1));
	}
	for (int i = 0; i < M; i++) {
		scanf("%d", &B[i]);
		if (hashtable.count(B[i])) {
			++cnt;
		}
	}

	printf("%d", cnt);

	return 0;

}