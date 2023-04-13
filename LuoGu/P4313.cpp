#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 1e5 + 3, INF = 1e9;

struct Edge {
	int to, rev, flow;
};
vector<Edge> G[N];

void addflow(int u, int v, int f) {
	Edge a = {v, (int)G[v].size(), f}, b = {u, (int)G[u].size(), 0};
	G[u].push_back(a);
	G[v].push_back(b);
}

int n, m, s, t;

int dep[N], gap[N];
void initISAP() {
	fill(dep, dep + t + 1, -1);
	gap[(dep[t] = 0)] = 1;
	
	queue<int> q; q.push(t);
	while (q.size()) {
		int x = q.front(); q.pop();
		for (auto e : G[x]) {
			if (dep[e.to] == -1)
				++gap[(dep[e.to] = dep[x] + 1)], q.push(e.to);
		}
	}
}

int cur[N];
int sap(int x, int flow) {
	if (x == t) return flow;
	
	int rest = flow;
    // 在O2下，不用当前弧优化更快
	// for (int &i = cur[x], ie = G[x].size(); i < ie; ++i) {
		// Edge &e = G[x][i];
    for (auto &e : G[x]) {
		if (dep[e.to] + 1 == dep[x] && e.flow) {
			int push = sap(e.to, min(e.flow, rest));
			if (push) {
				e.flow -= push, G[e.to][e.rev].flow += push;
				rest -= push;
			}
			if (!rest) return flow;
		}
	}
	
	if (--gap[dep[x]] == 0) dep[s] = t + 1;
	return ++gap[++dep[x]], flow - rest;
}

int id[101][101], afake[101][101], sfake[101][101];

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	cin >> n >> m;
	
	{
		int cur = s = 0;
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) id[i][j] = ++cur;
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) afake[i][j] = ++cur;
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) sfake[i][j] = ++cur;
		t = ++cur;
	}
	
	int x, sum = 0;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
		cin >> x; sum += x;
		addflow(s, id[i][j], x);
	}
	
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
		cin >> x; sum += x;
		addflow(id[i][j], t, x);
	}
	
	for (int fk, i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
		cin >> x; sum += x;
		addflow(s, (fk = afake[i][j]), x);
		addflow(fk, id[i][j], INF);
		if (i > 1) addflow(fk, id[i - 1][j], INF);
		if (j > 1) addflow(fk, id[i][j - 1], INF);
		if (i < n) addflow(fk, id[i + 1][j], INF);
		if (j < m) addflow(fk, id[i][j + 1], INF);
	}
	
	for (int fk, i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
		cin >> x; sum += x;
		addflow((fk = sfake[i][j]), t, x);
		addflow(id[i][j], fk, INF);
		if (i > 1) addflow(id[i - 1][j], fk, INF);
		if (j > 1) addflow(id[i][j - 1], fk, INF);
		if (i < n) addflow(id[i + 1][j], fk, INF);
		if (j < m) addflow(id[i][j + 1], fk, INF);
	}
	
	initISAP();
	int maxflow = 0;
	while (dep[s] <= t) {
		// fill(cur, cur + t + 1, 0);
		maxflow += sap(s, INF);
	}
//	cout << maxflow << '\n';
	cout << sum - maxflow << '\n';
	return 0;
}