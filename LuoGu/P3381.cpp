#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
	int to, flow, c, rev;
	Edge(int to, int flow, int c, int rev) : to(to), flow(flow), c(c), rev(rev) {}
};

const int N = 5e3 + 7, M = 5e4 + 7, INF = 0x3F3F3F3F;

int n, m, s, t;
vector< vector<Edge> > G;

inline void addFlow(int u, int v, int w, int c) {
	G[u].push_back(Edge(v, w, c, G[v].size()));
	G[v].push_back(Edge(u, 0, -c, G[u].size() - 1));
}

inline void read() {
	static int u, v, w, c;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d %d", &u, &v, &w, &c);
		addFlow(u, v, w, c);
	}
}

static int dis[N], inq[N], mif[N];
const Edge * ine[N];
inline bool spfa() {
	memset(dis, INF, sizeof(dis));	
	queue<int> q;
	q.push(s), dis[s] = 0, ine[t] = nullptr, mif[s] = INF, mif[t] = 0;
	while (q.size()) {
		int x = q.front(); q.pop();
		// printf("Q in %d\n", x);
		inq[x] = false;
		for (const Edge & e : G[x]) {
			// printf("\tEdge: {%d, %d, %d, %d}\n", e.to, e.flow, e.c, e.rev);
			if (e.flow && dis[e.to] > dis[x] + e.c) {
				dis[e.to] = dis[x] + e.c, ine[e.to] = &e;
				mif[e.to] = min(e.flow, mif[x]);
				if (!inq[e.to]) q.push(e.to), inq[e.to] = true;
			}
		}
	}
	return ine[t] != nullptr;
}

int main() {
	scanf("%d %d %d %d", &n, &m, &s, &t);
	G.resize(n + 1);
	read();
	
	int maxFlow = 0, minCost = 0;
	while (spfa()) {
		Edge * e;
		int now = t, c = mif[t];
		maxFlow += c;
		do {
			e = (Edge *)ine[now];
			Edge & rev = G[e->to][e->rev];
			e->flow -= c, rev.flow += c;
			minCost += c * e->c, now = rev.to;
		} while (now != s);
	}
	
	printf("%d %d\n", maxFlow, minCost);
	return 0;
}
