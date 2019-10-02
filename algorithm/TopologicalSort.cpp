// 2017029752_¹é½Â¼ö_12525

#include <stdio.h>
#include <stack>
#include <vector>
#include <functional>
using namespace std;

stack<int> pq;
int in[1001];
vector< vector< int > > adj;
vector<int> ans;
bool hasCycle;
bool visited[1001];
bool finished[1001];

int N;
void dfs(int here) {
	visited[here] = true;
	for (int i = 1; i <= N; i++) {
		if (!adj[here][i]) continue;

		if (!visited[i])
			dfs(i);
		else if (!finished[i])
			hasCycle = true;
	}
	finished[here] = true;
	ans.push_back(here);
}


int main(void) {
	scanf("%d", &N);

	adj.resize(N + 1, vector<int>(N + 1));

	int u, v;

	while (~scanf("%d %d", &u, &v)) {
		if (u == -1) break;
		adj[u][v] = 1;
		++in[v];
	}

	for (int i = 1; i <= N; i++) {
		if (!visited[i])
			dfs(i);
	}

	if (hasCycle) {
		printf("0");
		return 0;
	}

	printf("1\n");
	for (int i = 0; i < N; i++) {
		printf("%d ", ans[N - i - 1]);
	}

	return 0;
}