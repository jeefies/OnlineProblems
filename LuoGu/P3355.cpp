#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 202, S = N * N * 3, INF = 0x7F7F7F7F;

template<int V = S, int E = S * N>
class ISAP {
private:
	struct Edge {
		int to, flow, next;
	} edge[E];
	int head[V], tot;
	int dep[V], gap[V];
public:
	ISAP() : tot(1) {
	}
	
	void add(int u, int v, int f) {
		edge[++tot] = {v, f, head[u]}, head[u] = tot;
		edge[++tot] = {u, 0, head[v]}, head[v] = tot;
	}
	
	int n, s, t;
	void init(int n, int s, int t) {
		this->n = n, this->s = s, this->t = t;
		fill(dep, dep + n + 1, -1);
		gap[(dep[t] = 0)] = 1;
		queue<int> q; q.push(t);
		while (q.size()) {
			int x = q.front(); q.pop();
			for (int i = head[x]; i; i = edge[i].next) {
				int y = edge[i].to;
				if (edge[i].flow && dep[y] == -1) {
					++gap[(dep[y] = dep[x] + 1)], q.push(y);
				}
			}
		}
	}
	
	inline int sap(int x, int flow) {
		if (x == t) return flow;
		
		int rest = flow;
		for (int i = head[x]; i; i = edge[i].next) {
			int y = edge[i].to, &w = edge[i].flow;
			if (w <= 0 || dep[y] + 1 != dep[x]) continue;
			int f = sap(y, min(w, rest));
			if (f) {
				w -= f, edge[i ^ 1].flow += f;
				rest -= f;
			}
			if (!rest) return flow;
		}
		
		if (--gap[dep[x]] == 0) dep[s] = t + 1;
		return ++gap[++dep[x]], flow - rest;
	}
	
	int calc() {
		this->s = s;
		int maxflow = 0;
		while (dep[s] <= n) maxflow += sap(s, INF);
		return maxflow;
	}
};
ISAP<> isap;

int n, m, s, t;
int forbid[N][N];
int hid[N][N], bid[N][N];
void read() {
	cin >> n;
	int cur = s = 0;
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j) 
		hid[i][j] = ++cur, bid[i][j] = ++cur;
	t = ++cur;
	
	cin >> m;
	for (int x, y, i = 0; i < m; ++i) {
		cin >> x >> y;
		forbid[x][y] = true;
	}
}

void build() {
	static int dx[] = {1, 2, 1, 2, -1, -2, -1, -2};
	static int dy[] = {2, 1, -2, -1, 2, 1, -2, -1};
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
		if (forbid[i][j]) continue;
		if ((i + j) & 1) {
			isap.add(s, hid[i][j], 1);
			for (int k = 0; k < 8; ++k) {
				int nx = i + dx[k], ny = j + dy[k];
				if (1 <= nx && nx <= n && 1 <= ny && ny <= n && !forbid[nx][ny])
					isap.add(hid[i][j], bid[nx][ny], INF);
			}
		} else isap.add(bid[i][j], t, 1);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(false);
	read();
	build();
	
	isap.init(n, s, t);
	int maxflow = isap.calc();
	cout << n * n - m - maxflow;
}