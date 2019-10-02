// 2017029752_¹é½Â¼ö_12525

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct Vertex
{
	int s;
	int d;
	int weight;
};

priority_queue<Vertex> heap;
int adj[1005][1005];
int result[1005][3];
int parent[1001];

bool operator<(Vertex u, Vertex v);
int find(int id);
int Kruskal();

int N;
int s_size;

int main(void) {
	int x, y, w;
	scanf("%d", &N);

	while (scanf("%d %d %d", &x, &y, &w) != EOF) {
		adj[x][y] = adj[y][x] = w;
	}

	int num = Kruskal();
	printf("%d\n", num);

	for (int i = 0; i < num; ++i) {
		printf("%d %d %d\n", result[i][0], result[i][1], result[i][2]);
	}

	return 0;
}

bool operator<(Vertex u, Vertex v)
{
	if (u.weight == v.weight)
	{
		if (u.s == v.s)
		{
			return u.d > v.d;
		}
		else
		{
			return u.s > v.s;
		}
	}
	else
	{
		return u.weight > v.weight;
	}
}

int find(int id)
{
	while (parent[id] >= 0)
	{
		id = parent[id];
	}
	return id;
}

int Kruskal()
{
	int i, j, edge_a = 0, uset, vset;
	Vertex e;
	s_size = N;
	for (int i = 0; i < N; ++i)
	{
		parent[i] = -1;
	}
	for (i = 1; i < N; i++)
	{
		for (j = i + 1; j <= N; j++)
		{
			if (adj[i][j] < 2147483647)
			{
				e.weight = adj[i][j];
				e.s = i;
				e.d = j;
				if (e.weight != 0)
				{
					heap.push(e);
				}
			}
		}
	}
	while (edge_a < N - 1)
	{
		e = heap.top();
		heap.pop();
		uset = find(e.s);
		vset = find(e.d);
		if (uset != vset)
		{
			result[edge_a][0] = e.s;
			result[edge_a][1] = e.d;
			result[edge_a][2] = e.weight;
			parent[uset] = vset;
			s_size--;
			edge_a++;
		}
	}
	return edge_a;
}