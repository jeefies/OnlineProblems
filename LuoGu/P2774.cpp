#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
const int N = 102, INF = 0x7FFFFFFF;

template<int V = 20000, int E = 200000>
class ISAP {
private:
	struct Edge {
		int to, flow, next;
	} edge[E];
	int head[V], tot;
	int dep[V], gap[V << 1];
public:
	ISAP() : tot(1) {
	}
	
	void add(int u, int v, int f) {
		clog << u << " " << v << " " << f << '\n';
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
				if (dep[y] == -1) {
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

int n, m, s, t, sum = 0;
int mp[N][N], hid[N][N];

void read() {
	int cur = s = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
		cin >> mp[i][j], hid[i][j] = ++cur, sum += mp[i][j];
	t = ++cur;
	
	clog << "Read Done\n";
}

void build() {
	static int dx[] = {1, 0, -1, 0};
	static int dy[] = {0, 1, 0, -1};
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) if ((i + j) & 1) {
			isap.add(s, hid[i][j], mp[i][j]);
			for (int k = 0; k < 4; ++k) {
				int nx = i + dx[k], ny = j + dy[k];
				if (1 <= nx && nx <= n && 1 <= ny && ny <= m)
					isap.add(hid[i][j], hid[nx][ny], INF);
			}
		} else isap.add(hid[i][j], t, mp[i][j]);
	clog << "Build Done\n";
}

int main() {
//	cin.tie(0)->sync_with_stdio(false);
	read();
	build();
	isap.init(t, s, t);
	clog << "Init Done\n";
	cout << sum - isap.calc() << '\n';
}