#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

/*
采用前向星（边表）的方式进行存储和遍历
采用了搜索的方式(dfs/bfs)
当然，这是一个很无脑的方式 
*/

struct Edge {
	int to, w, next;
};

const int N = 1e5 + 2;
int head[N] = {0}, size = 0;
Edge edge[N];

void add_route(int x, int y, int w) {
	++size;
	edge[size].next = head[x], head[x] = size;
	edge[size].to = y, edge[size].w = w;
}

static char vis[N];
int dfs(int i) {
	vis[i] = 1;
	int maxn = i;
	for (int t = head[i]; t; t = edge[t].next) {
		if (!vis[edge[t].to]) {
			maxn = max(maxn, dfs(edge[t].to));
		}
	}
	return maxn;
}

int bfs(int org) {
	static int stk[N], tail; tail = -1; // 栈 
	int maxn = stk[++tail] = org; // 初始化 
	while (tail >= 0) {
		int i = stk[tail--];
		vis[i] = 1, maxn = max(maxn, i);
		for (int t = head[i]; t; t = edge[t].next) {
			if (!vis[edge[t].to]) // 如果没有走过，入栈 
				stk[++tail] = edge[t].to;
		}
	}
	return maxn;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int u, v;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		add_route(u, v, 0);
	}
	
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		cout << bfs(i) << ' ';
	}
	return 0;
}
