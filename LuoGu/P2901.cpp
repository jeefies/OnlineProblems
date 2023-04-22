#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
const int N = 5e3 + 3;

int n, m;
int rest[N];

struct RNode {
	int x;
	int c;
	bool operator < (const RNode &r) const {
		return c > r.c;
	}
};

class Graph {
private:
	struct Edge {
		int to;
		int w;
	};
	vector<Edge> G[N];
public:
	inline void add(int u, int v, int w) {
		G[u].push_back({v, w});
	}
	
	void djk(int s, int * dis) {
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
	
	int work(int s, int t, int k, int * dis, vector<int> &res) {
		priority_queue<RNode> q; q.push({s, dis[s]});
		
		// TODO !!!
		int cnt = 0;
		while (q.size()) {
			auto x = q.top(); q.pop();
			// cout << "Q top " << x.x << " " << x.c << '\n';
			if (x.x == t) {
                res.push_back(x.c);
                if (++cnt == k) break;
            }

			for (auto e : G[x.x]) {
				q.push({e.to, x.c - dis[x.x] + e.w + dis[e.to]});
				// cout << "\tQ push " << e.to << ' ' << x.c - dis[x.x] + e.w + dis[e.to] << '\n';
			}
		}
		return -1;
	}
} rg, g;

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
    int k;
	cin >> n >> m >> k;
	
	for (int s, t, e, i = 1; i <= m; ++i) {
		cin >> s >> t >> e;
		g.add(s, t, e);
		rg.add(t, s, e);
	}
	
	fill(rest, rest + n + 1, 2e9);
	rg.djk(1, rest);
	
	for (int i = 1; i <= n; ++i) {
		// cout << "Node " << i << " Min dis = " << rest[i] << '\n';
	}
	
    vector<int> res;
	g.work(n, 1, k, rest, res);
    for (int i = 0; i < k; ++i) {
        cout << (i < res.size() ? res[i] : -1) << '\n';
    }
	return 0;
}