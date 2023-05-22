#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 1000;

class Graph {
private:
	int deg[N];
	vector<int> G[N];
public:
	inline void add(int u, int v) {
		G[u].push_back(v);
		++deg[v];
	}

	inline void dfs(int x) {
		cout << x << ' ';
		for (int y : G[x]) dfs(y);
	}

	inline void output(int n) {
		for (int i = 1; i <= n; ++i) {
			if (!deg[i]) dfs(i), cout << '\n';
		}
	}
} g;

class ISAP {
private:
	struct Edge {
		int to, flow, next;
	} edge[100000];
	int head[N], tot;
	int n, s, t;
	int dep[N], gap[N << 1];
public:
	ISAP() : tot(1) {}
	inline void addflow(int u, int v, int f) {
		edge[++tot] = {v, f, head[u]}, head[u] = tot;
		edge[++tot] = {u, 0, head[v]}, head[v] = tot;
	}

	inline void init(int n, int s, int t) {
		this->n = n, this->s = s, this->t = t;
		fill(dep, dep + n + 1, -1);
		
		gap[(dep[t] = 0)] = 1;
		queue<int> q; q.push(t);

		while (q.size()) {
			int x = q.front(); q.pop();
			for (int i = head[x]; i; i = edge[i].next) {
				int to = edge[i].to;
				if (dep[to] == -1) 
					++gap[(dep[to] = dep[x] + 1)], q.push(to);
			}
		}
	}

	inline int sap(int x, int flow) {
		if (x == t) return flow;

		int rest = flow;
		for (int i = head[x]; i; i = edge[i].next) {
			auto &e = edge[i];
			if (dep[e.to] + 1 == dep[x] && e.flow > 0) {
				int push = sap(e.to, min(e.flow, rest));
				if (push) {
					e.flow -= push, edge[i ^ 1].flow += push;
					rest -= push;
				}
				if (!rest) return flow;
			}
		}

		if (--gap[dep[x]] == 0) dep[s] = n + 1;
		return ++gap[++dep[x]], flow - rest;
	}

	inline void build(Graph &g, int n) {
		for (int x = 1; x <= n; ++x) {
			for (int i = head[x]; i; i = edge[i].next) {
				if (edge[i].to > 0 && edge[i ^ 1].flow > 0) g.add(x, edge[i].to - n);
			}
		}
	}

	inline int maxflow() {
		int flow = 0, inf = 0x7FFFFFF0;
		while (dep[s] <= n) flow += sap(s, inf);
		return flow;
	}
} isap;

int main() {
	int n, m;
	cin >> n >> m;

	int s = 0, t = n + n + 1;
	for (int x, y, i = 0; i < m; ++i) {
		cin >> x >> y;
		isap.addflow(x, y + n, 1);
	}

	for (int i = 1; i <= n; ++i) {
		isap.addflow(s, i, 1), isap.addflow(i + n, t, 1);
	}

	isap.init(t, s, t);
	int flow = isap.maxflow();
	isap.build(g, n);
	g.output(n);
	cout << n - flow << '\n';
	return 0;
}
