#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

struct Edge {
	int to;
	int next;
	int w;
};

const int N = 2501, INF = 0x3F3F3F3F;
int n, m, s, t;
// 向前星 (this has no english name, because it's "fucked" by chinese IOers)
int head[N], size = 0;
struct Edge edge[N * 2];

void add_route(int u, int v, int w) {
	++size;
	edge[size].next = head[u], head[u] = size;
	edge[size].to = v, edge[size].w = w;
}

int djk(int s, int e) {
	static int dis[N]; memset(dis, 0x3F, sizeof(dis));
	static int vis[N]; memset(vis, 0, sizeof(vis));
	
	// init
	for (int t = head[s]; t; t = edge[t].next)
		dis[edge[t].to] = edge[t].w;
		
	vis[s] = true;
	
	while (true) {
		int mmin = INF, mpos = -1;
		// searching for the smallest point
		for (int i = 1; i <= n; i++) {
			if (!vis[i] && dis[i] < mmin) mmin = dis[i], mpos = i;
		}
		
		// every point is visited
		if (mpos == -1) break;
		
		vis[mpos] = 1;
		// we should enum every point the mpos can reach to
		for (int t = head[mpos]; t; t = edge[t].next) {
			int to = edge[t].to;
			if (!vis[to]) dis[to] = min(dis[to], dis[mpos] + edge[t].w);
		}
	}
	return dis[e];
}

int main() {
	scanf("%d %d %d %d", &n, &m, &s, &t);
	
	int u, v, w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		add_route(u, v, w); add_route(v, u, w);
	}
	
	printf("%d\n", djk(s, t));
	return 0;
}
