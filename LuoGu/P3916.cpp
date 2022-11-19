#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

/*
����ǰ���ǣ��߱��ķ�ʽ���д洢�ͱ���
�����������ķ�ʽ(dfs/bfs)
��Ȼ������һ�������Եķ�ʽ 
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
	static int stk[N], tail; tail = -1; // ջ 
	int maxn = stk[++tail] = org; // ��ʼ�� 
	while (tail >= 0) {
		int i = stk[tail--];
		vis[i] = 1, maxn = max(maxn, i);
		for (int t = head[i]; t; t = edge[t].next) {
			if (!vis[edge[t].to]) // ���û���߹�����ջ 
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
