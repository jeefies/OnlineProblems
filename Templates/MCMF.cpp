#include <iostream>
#include <algorithm>
#include <vector>
#include <queue> 

using namespace std;
const int N = 51, S = N * N * 3;
const int INF = 0x7F7F7F7F;

struct Edge {
	int to, flow, cost, next;
} edge[N * N * N];
int head[S], tot = 1;
void add(int u, int v, int f, int c) {
	edge[++tot] = {v, f, c, head[u]}, head[u] = tot;
	edge[++tot] = {u, 0, -c, head[v]}, head[v] = tot;
}

int n, k;
int mp[N][N];
void read() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			cin >> mp[i][j];
	}
}

int s, t;
int inID[N][N], outID[N][N];
void build() {
	int cur = s = 0;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) inID[i][j] = ++cur;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) outID[i][j] = ++cur;
	t = ++cur;
	
	add(s, inID[1][1], k, 0);
	add(outID[n][n], t, k, 0);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			add(inID[i][j], outID[i][j], INF, 0);
			add(inID[i][j], outID[i][j], 1, -mp[i][j]);
			
			if (i < n) add(outID[i][j], inID[i + 1][j], INF, 0);
			if (j < n) add(outID[i][j], inID[i][j + 1], INF, 0);
			if (i < n && j < n) add(outID[i][j], inID[i][j + 1], INF, 0);
		}
	}
	clog << "Build Done\n";
}

int inq[S], dis[S], pre[S], flow[S];
bool SPFA() {
	fill(dis, dis + t + 1, INF);
	
	queue<int> q; q.push(s);
	dis[s] = 0, pre[s] = 0, flow[s] = INF;
	while (q.size()) {
		int x = q.front(); q.pop();
		
		inq[x] = false;
		for (int i = head[x]; i; i = edge[i].next) {
			int y = edge[i].to, c = edge[i].cost, w = edge[i].flow;
			if (edge[i].flow > 0 && dis[y] > dis[x] + c) {
				dis[y] = dis[x] + c;
				pre[y] = i, flow[y] = min(flow[x], w);
				if (!inq[y]) inq[y] = true, q.push(y);
			}
		}
	}
	
	return dis[t] != INF;
}

void MCMF(int &maxflow, int &mincost) {
	maxflow = mincost = 0;
	while (SPFA()) {
		maxflow += flow[t];
		mincost += dis[t] * flow[t];
		clog << "Loop +1: mf, mc to " << maxflow << ' ' << mincost << '\n';
		for (int x = t; x ^ s; x = edge[pre[x] ^ 1].to) {
			edge[pre[x]].flow -= flow[t];
			edge[pre[x] ^ 1].flow += flow[t];
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(false);
	read();
	build();
	int maxflow, mincost;
	MCMF(maxflow, mincost);
	cout << -mincost << '\n'; 
}
