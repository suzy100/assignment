// 2017029752_¹é½Â¼ö_12525

#include <stdio.h>
#include <vector>
using namespace std;

vector <int> adj[1001];
int comp[1001], visit[1001];
int cnt = 0;


void dfs(int x);

int main()
{
	int N, x , y;
	scanf("%d", &N);
	while (scanf("%d%d", &x, &y) != EOF)
	{
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	for (int i = 1; i <= N; i++)
	{
		if (!visit[i])
		{
			cnt++;
			dfs(i);
		}
	}
	printf("%d\n", cnt);
	for (int i = 1; i <= N; i++)
	{
		printf("%d\n", comp[i]);
	}
}

void dfs(int x)
{
	visit[x] = 1;
	comp[x] = cnt;
	vector <int> ::iterator it;
	for (it = adj[x].begin(); it != adj[x].end(); it++)
	{
		if (!visit[*it])
		{
			dfs(*it);
		}
	}
}