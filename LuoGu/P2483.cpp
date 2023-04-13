#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
const int N = 5e3 + 3;

int n, m;
double E;
double rest[N];

struct RNode {
	int x;
	double c;
	bool operator < (const RNode &r) const {
		return c > r.c;
	}
};

class Graph {
private:
	struct Edge {
		int to;
		double w;
	};
	vector<Edge> G[N];
public:
	inline void add(int u, int v, double w) {
		G[u].push_back({v, w});
	}
	
	void djk(int s, double * dis) {
		vector<bool> vis(n + 1);
		priority_queue<RNode> q; q.push({s, 0});
		
		while (q.size()) {
			auto x = q.top(); q.pop();
			if (vis[x.x]) continue;
			vis[x.x] = true;
			dis[x.x] = x.c;
			for (auto e : G[x.x]) {
				if (!vis[e.to]) q.push({e.to, x.c + e.w});
			}
		}
	}
	
	void work(int t, int * dis) {
		priority_queu<RNode> q; q.push({1, 0});
		
		// TODO !!!
		int cnt = 0;
		while (q.size()) {
			auto x = q.top(); q.pop();
			if (x.x == t) {
				if (x.c > E + 1e-10) return cnt;
				else ++cnt;
			}
		}
	}
} rg, g;

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	cin >> n >> m >> E;
	
	for (int s, t, i = 1; i <= m; ++i) {
		double e; cin >> s >> t >> e;
		g.add(s, t, e);
		rg.add(t, s, e);
	}
	
	fill(rest, rest + n + 1, 2e9);
	rg.djk(n, rest);
	
	for (int i = 1; i <= n; ++i) {
		cout << "Node " << i << " Min dis = " << rest[i] << '\n';
	}
	
	cout << g.work(n, rest) << '\n';
	return 0;
}