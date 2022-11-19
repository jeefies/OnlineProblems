#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

/*
����ǰ���ǣ��߱��ķ�ʽ���д洢�ͱ���
�����˴Ӹߵ��͵�������ʽ����Ȼ�����Ҳ���� 
�������Թ�ȫ������ 
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

static int cached[N] = {0};
int dfs(int i, int big) {
	if (cached[i]) {
		return cached[i];
	}
	
	cached[i] = big;
	for (int t = head[i]; t; t = edge[t].next) {
		if (!cached[edge[t].to])
			dfs(edge[t].to, big);
	}
	return big;
}

// bigֻ��Ϊ��ռλ��û���á� 
void bfs(int org, int big) {
	if (cached[org]) return;
	
	static int stk[N]; int tail = -1; // ��ʼ��ջ 
	stk[++tail] = org;
	while (tail >= 0) {
		int i = stk[tail--];
		cached[i] = org;
		for (int t = head[i]; t; t = edge[t].next) {
			if (!cached[edge[t].to])
				stk[++tail] = edge[t].to;
		}
	}
} 

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int u, v;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		add_route(v, u, 0);
	}
	
	for (int i = n; i >= 1; i--) dfs(i, i);
	for (int i = 1; i <= n; i++) printf("%d ", cached[i]);
	return 0;
} 
