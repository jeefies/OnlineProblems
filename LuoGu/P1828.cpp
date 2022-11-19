#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int N = 4000, INF = 0x3F3F3F3F;

struct Edge {
	int to, next, w;
};
int head[N], size = 0;
Edge edge[N];

void add(int u, int v, int w) {
	++size;
	edge[size].next = head[u], head[u] = size;
	edge[size].to = v, edge[size].w = w;
}

void spfa(int s, int * dis) {
	static int inq[N]; memset(inq, 0, sizeof(inq));
	
	queue<int> que; que.push(s);
	dis[s] = 0;
	
	while (!que.empty()) {
		int top = que.front(); que.pop();
		inq[top] = false;
		
		for (int t = head[top]; t; t = edge[t].next) {
			int to = edge[t].to;
			if (dis[to] > dis[top] + edge[t].w) {
				dis[to] = dis[top] + edge[t].w;
				if (!inq[to]) inq[to] = true, que.push(to);
			}
		} 
	}
}

int main() {
	int n, p, c;
	scanf("%d %d %d", &n, &p, &c);
	
	static int w[N];
	for (int i = 1; i <= n; i++) scanf("%d", w + i);
	
	int a, b, d;
	for (int i = 1; i <= c; i++) {
		scanf("%d %d %d", &a, &b, &d);
		add(a, b, d); add(b, a, d);
	}
	
	static int total[N] = {0};
	static int dis[N] = {0};
	for (int i = 1; i <= n; i++) {
		memset(dis, 0x3F, sizeof(dis));
		spfa(w[i], dis);
		for (int i = 1; i <= p; i++) if (total[i] < INF) total[i] += dis[i];
	}
	
	int m = INF;
	for (int i = 1; i <= p; i++) m = min(m, total[i]);
	printf("%d", m);
}
