#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <bitset>

using namespace std;
const int N = 203;

bool rch[N][N];
class Edge {
public:
	int to, flow, next;
};

class ISAP {
private:
	Edge edge[100000];
	int head[N], tot;
	int n, s, t;
	int dep[N], gap[N << 1];
public:
	ISAP() : tot(1) {}
	void clear() { tot = 1; fill_n(head, N, 0); }

	inline void addflow(int u, int v, int f) {
		edge[++tot] = {v, f, head[u]}, head[u] = tot;
		edge[++tot] = {u, 0, head[v]}, head[v] = tot;
	}

	inline void init(int n, int s, int t) {
		this->n = n, this->s = s, this->t = t;
		fill(dep, dep + n + 1, -1);
		fill(gap, gap + n + 1, 0);
		
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

	inline int maxflow() {
		int flow = 0, inf = 0x7FFFFFF0;
		while (dep[s] <= n) flow += sap(s, inf);
		return flow;
	}
} isap;

int res[N], del[N], color[N], flag[N];
int main() {
	int n, m;
	cin >> n >> m;

	for (int u, v, i = 0; i < m; ++i) {
		cin >> u >> v;
		rch[u][v] = true;
	}

	// for (int i = 1; i <= n; ++i) {
	// 	for (int j = 1; j <= n; ++j)
	// 		if (rch[i][j]) rch[i] |= rch[j];
	// }
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				rch[i][j] |= rch[i][k] & rch[k][j];
	}

	isap.clear();
	int s = 0, t = n + n + 1;
	for (int i = 1; i <= n; ++i) isap.addflow(s, i, 1), isap.addflow(i + n, t, 1);
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
		if (rch[i][j]) isap.addflow(i, j + n, 1);
	}

	isap.init(t, s, t);
	int ret = n - isap.maxflow();
	printf("%d\n", ret);

	for (int dx = 1; dx <= n; ++dx) {
		isap.clear();
		int dots = 0;
		for (int i = 1; i <= n; ++i) 
			del[i] = (i == dx) || rch[i][dx] || rch[dx][i];
		for (int i = 1; i <= n; ++i) if (!del[i]) 
			isap.addflow(s, i, 1), isap.addflow(i + n, t, 1), ++dots;
		for (int i = 1; i <= n; ++i) if (!del[i]) {
			for (int j = 1; j <= n; ++j) if (!del[j]) {
				if (rch[i][j]) isap.addflow(i, j + n, 1);
			}
		}

		isap.init(t, s, t);
		int flow = isap.maxflow();
		res[dx] = dots - flow == ret - 1;
	}

	for (int i = 1; i <= n; ++i) {
		if (res[i] && !color[i]) {
			color[i] = i, flag[i] = 1;
			for (int j = 1; j <= n; ++j) {
				if (rch[i][j] || rch[j][i]) color[j] = i;
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		putchar('0' + flag[i]);
	} puts("");
	for (int i = 1; i <= n; ++i) {
		putchar('0' + res[i]);
	} puts("");
	return 0;
}

