#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

struct Edge {
	int to;
	int next;
	int w;
};

const int N = 1e5 + 1, INF = 0x7F7F7F7F;
int n, m, s;
// 向前星 (this has no english name, because it's "fucked" by chinese IOers)
int head[N], size = 0;
struct Edge edge[N * 5];

void add_route(int u, int v, int w) {
	++size;
	edge[size].next = head[u], head[u] = size;
	edge[size].to = v, edge[size].w = w;
}

struct P {
	int w, p;
	bool operator > (const P & p) const {
		return w > p.w;
	}
};
int * djk(int s) {
	static int dis[N]; memset(dis, 0x7F, sizeof(dis));
	static int vis[N]; memset(vis, 0, sizeof(vis));
	
	// init
	// if use priority_queue, we don't need to init the dis array at first.
	dis[s] = 0;

	// use a heap-like object to make searching for the smallest point quicker	
	priority_queue<P, vector<P>, greater<P> > que;
	P p = {0, s};
	que.push(p); // init que
	while (!que.empty()) {
		p = que.top(); que.pop();
		int mpos = p.p;
		if (vis[mpos]) continue;
		vis[mpos] = true;
		
		for (int t = head[mpos]; t; t = edge[t].next) {
			int to = edge[t].to;
			if (!vis[to] && dis[to] > dis[mpos] + edge[t].w) {
				dis[to] = dis[mpos] + edge[t].w;
				p.w = dis[to], p.p = to; que.push(p);
			}
		}
	}
	
	return dis;
}

int main() {
	scanf("%d %d %d", &n, &m, &s);
	
	int u, v, w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		add_route(u, v, w);
	}
	
	int * dis = djk(s);
	for (int i = 1; i <= n; i++) {
		if (dis[i] == INF) printf("%d ", (1ll << 31)-1);
		else printf("%d ", dis[i]);
	}
	return 0;
}
