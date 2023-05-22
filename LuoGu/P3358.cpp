#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 10003, INF = 0x7FFFFFFF;

struct Edge {
	int to, next, flow, cost;
} edge[100000];
int head[N], tot = 1;
void add(int u, int v, int f, int c) {
	// printf("add %d <-{%d, %d}-> %d\n", u, f, c, v);
	edge[++tot] = {v, head[u], f, c}, head[u] = tot;
	edge[++tot] = {u, head[v], 0, -c},head[v] = tot;
}

int n, k;
int dis[N], inq[N], pre[N], flow[N];
bool SPFA(int s, int t) {
	// printf("in SPFA\n");
	fill(dis, dis + n + n + 2, -INF);

	dis[s] = 0, flow[s] = INF;
	queue<int> q; q.push(s);

	while (q.size()) {
		int x = q.front(); q.pop();
		// printf("At %d:\n", x);
		inq[x] = false;
		for (int i = head[x]; i; i = edge[i].next) {
			Edge &e = edge[i];
			// printf("\tnext edge{%d, %d, %d}\n", e.to, e.flow, e.cost);
			if (e.flow > 0 && dis[e.to] < dis[x] + e.cost) {
				dis[e.to] = dis[x] + e.cost;
				// printf("\tUpdate!! dis[%d] = %d\n", e.to, dis[e.to]);
				pre[e.to] = i, flow[e.to] = min(flow[x], e.flow);
				if (!inq[e.to]) q.push(e.to), inq[e.to] = true;
			}
		}
	}

	// printf("SPFA done\n");
	return dis[t] != -INF;
}

int maxflow, maxcost;
void MCMF(int s, int t) {
	maxflow = maxcost = 0;
	while (SPFA(s, t)) {
		maxcost += flow[t] * dis[t];
		maxflow += flow[t];
		// printf("cost, flow updated to: %d, %d\n", maxcost, maxflow);
		for (int x = t; x ^ s; x = edge[pre[x] ^ 1].to) {
			edge[pre[x]].flow -= flow[t];
			edge[pre[x] ^ 1].flow += flow[t];
		}
	}
}

struct Dot {
	int l, r;
} dots[N];
int apps[N], apc = 0;
int main() {
	// cin.tie(0)->sync_with_stdio(false);

	cin >> n >> k;

	for (int l, r, i = 0; i < n; ++i) {
		cin >> l >> r;
		dots[i] = {l, r};
		apps[apc++] = l, apps[apc++] = r;
	}

	sort(apps, apps + apc);
	int *ae = unique(apps, apps + apc);
	for (int i = 0; i < n; ++i) {
		dots[i].l = lower_bound(apps, ae, dots[i].l) - apps + 1;
		dots[i].r = lower_bound(apps, ae, dots[i].r) - apps + 1;
	}

	int s = 0, t = ae - apps + 1;
	for (int i = 1; i <= t; ++i) {
		add(i - 1, i, k, 0);
	}

	for (int i = 0; i < n; ++i) {
		Dot &dot = dots[i];
		add(dot.l, dot.r, 1, apps[dot.r - 1] - apps[dot.l - 1]);
	}

	MCMF(s, t);
	cout << maxcost << '\n';
}
