#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <cstring> 

using std::deque;

const int N = 2e3 + 7, M = 5e5 + 7, INF = 0x7F7F7F7F;

int n, m, s, t;

int to[M], nex[M], wi[M] = {INF};
int head[N], tot = 1;

void add(int u, int v, int w) {
	++tot;
	to[tot] = v, nex[tot] = head[u], wi[tot] = w, head[u] = tot;
}

void read() {
	scanf("%d %d %d %d", &n, &m, &s, &t);

	int u, v, w;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d %d", &u, &v, &w);
		add(u, v, w);
		add(v, u, 0);
	}
}

int dis[N], vis[N], vt = 0;
int now[N];
// return true if exists non-0 road to t
bool bfs() {
	memset(dis, 0, sizeof(dis)); dis[s] = 1;
	
	deque<int> que;
	que.push_back(s);
	while (que.size()) {
		int x = que.front(); que.pop_front();
		for (int y, i = head[x]; i; i = nex[i]) {
			if (!dis[y = to[i]] && wi[i]) {
				dis[y] = dis[x] + 1, now[y] = head[y];
				que.push_back(y);
				// if (y == t) return true;
			}
		}
	}
	return dis[t];
}

#define min(x, y) ((x) < (y) ? (x) : (y))

#define data long long
data dinic(int x, data maxFlow) {
	if (x == t) return maxFlow;
	data rest = maxFlow, k;
	for (int y, i = head[x]; i && rest; i = nex[i]) {
		now[x] = i;
		if (dis[y = to[i]] == dis[x] + 1 && wi[i]) {
			k = dinic(y, min(rest, wi[i]));
			if (!k) dis[y] = 0;
			wi[i] -= k, wi[i ^ 1] += k;
			rest -= k;
		}
	}
	return maxFlow - rest;
}

int main() {
	read();
	data maxFlow = 0, flow;
	while (bfs()) {
		while ((flow = dinic(s, INF))) maxFlow += flow;
	} 
	printf("%lld\n", maxFlow);
}
