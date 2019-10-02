// 2017029752_¹é½Â¼ö_12525

#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int dist[5002], ans = 0;
vector<vector<pair<int, int> > > graph;

int main() {
	int N, cur, num, des, w;
	scanf("%d", &N);
	graph.resize(N + 1);

	for (int i = 1; i <= N; i++) {
	
		scanf("%d %d", &cur, &num);

		for (int i = 1; i <= num; i++) {
			scanf("%d", &des);
			scanf("%d", &w);
			graph[cur].push_back(make_pair(des, w));
		}
	}

	memset(dist, -1, sizeof(dist));
	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(0,1));

	while (pq.size()) {
		int here = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();

		if (dist[here] != -1) continue;
		dist[here] = cost;
		
		for (vector<pair<int, int> >::iterator it = graph[here].begin(); it != graph[here].end(); ++it) {
			int next = it->first;
			int acost = -it->second - cost;
		
			if (dist[next] != -1) continue;
			pq.push(make_pair(acost,next));
		}
	}
	
	for (int i = 1; i <= N; i++) {
		if (dist[i] == -1) printf("Unknown\n");
		else if (dist[i] > ans) ans = dist[i];
	}
	
	printf("%d\n", ans);
	
	return 0;
}
