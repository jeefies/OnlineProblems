#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;
const int N = 1e5 + 7;

typedef long long int Data;

class ISAP {
private:
	struct Edge {
		int to, rev;
		Data flow;
		Edge(int to, int rev, Data flow) : to(to), rev(rev), flow(flow) {}
	};
	vector<int> gap, dep;
	vector<Edge> G[N];
public:
	int n, m, s, t;
	inline void addflow(int u, int v, int w) {
		G[u].push_back(Edge(v, G[v].size(), w));
		G[v].push_back(Edge(u, G[u].size() - 1, 0));
	}

	inline void read() {
		cin >> n >> m >> s >> t;
		for (int u, v, w, i(0); i < m; ++i) {
			cin >> u >> v >> w;
			addflow(u, v, w);
		}
	}
	
	inline void init() {
		vector<int> q(n + 2);
		gap.assign(n * 2, 0), dep.assign(n + 1, -1);
		dep[t] = 0, gap[0] = 1;
		
		int head(0), tail(1), x, y;
        q[head] = t;
		while (head ^ tail) {
			x = q[head++];
			for (auto &e : G[x]) {
				if (dep[(y = e.to)] == -1)
					++gap[(dep[y] = dep[x] + 1)], q[tail++] = y;
			}
		}
	}
	
	inline Data sap(int x, Data flow) {
		if (x == t) return flow;
		
		Data rest = flow;
		for (auto &e : G[x]) {
			if (dep[e.to] + 1 == dep[x] && e.flow) {
				Data f = sap(e.to, min(rest, e.flow));
				if (f) {
					e.flow -= f, G[e.to][e.rev].flow += f;
					rest -= f;
				}
				if (!rest) return flow;
			}
		}
		
		if (--gap[dep[x]] == 0) dep[s] = n + 1;
		return ++gap[++dep[x]], flow - rest;
	}
	
	inline Data calc() {
		Data maxflow = 0, INF = numeric_limits<Data>::max();
		while (dep[s] <= n) {
			maxflow += sap(s, INF);
		}
		return maxflow;
	}
} isap;

int main() {
	cin.tie(0)->sync_with_stdio(false);
	 
	isap.read();
	isap.init();
	cout << isap.calc() << '\n';
	return 0;
}