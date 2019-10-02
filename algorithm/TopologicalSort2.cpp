// 2017029752_¹é½Â¼ö_12525

#include <stdio.h>
#include <stack>
#include <vector>
#include <functional>
using namespace std;

stack<int> pq;
int in[1001];
vector<int> adj;
vector<int> ans;
bool hasCycle;
bool visited[1001];
bool finished[1001];
void dfs(int here) {
	visited[here] = true;
	for (int i = 0; i < adj[here].size(); i++) {
		if (!visited[next])
			dfs(next);
		else if (!finished[next])
			hasCycle = true;
	}
	finished[v] = true;
	ans.push_back(v);
}


int main(void) {
	int N;
	scanf("%d", &N);
	
	int u, v;

	while (~scanf("%d %d", &u, &v)) {
		if (u == -1) break;
		adj[u].push_back(v);
		++in[v];
	}

	for (int i = 1; i <= N; i++) {
		if (!visited[i])
			ds(i);
	}

	if (ans.size() != N) {
		printf("0");
		return 0;
	}

	printf("1\n");
	for (int i = 0; i < N; i++) {
		printf("%d ", ans[N - i - 1]);
	}

	return 0;
}