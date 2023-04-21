#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>

using namespace std;
#define data int
const int N = 5e6 + 3, INF = 0x3F3F3F3F;

class ISAP {
private:
	struct Edge {
		int to, rev;
		data flow;
		Edge(int to, int rev, data flow) : to(to), rev(rev), flow(flow) {}
	};
	vector<int> gap, dep;
	vector<Edge> G[N];
    int q[N];
public:
	int n, m, s, t;
	inline void addflow(int u, int v, int w) {
        // printf("%d %d %d\n", u, v, w);
		G[u].push_back(Edge(v, G[v].size(), w));
		G[v].push_back(Edge(u, G[u].size() - 1, 0));
	}

	inline void init(int n, int s, int t) {
        this->n = n, this->s = s, this->t = t;

		gap.assign(n << 3, 0), dep.assign(n << 3, -1);
		gap[(dep[t] = 0)] = 1;
		
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
	
	inline data sap(int x, data flow) {
		if (x == t) return flow;
		
		data rest = flow;
		for (auto &e : G[x]) {
			if (dep[e.to] + 1 == dep[x] && e.flow) {
				data f = sap(e.to, min(rest, e.flow));
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
	
	inline data calc() {
		data maxflow = 0;
		while (dep[s] <= n) {
			maxflow += sap(s, INF);
		}
		return maxflow;
	}
} isap;

const int S = 500;
int n;
char mp[S][S];
int id[S][S];

int main() {
    // cin.tie(0)->sync_with_stdio(false);
    cin >> n;

    int cur = 0;
    for (int i = 1; i <= n; ++i) cin >> mp[i] + 1;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        id[i][j] = ++cur;
    }

    int s = 0, t = cur + (n * n) * 4 + 1, sum = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        if (mp[i][j] == 'B') ((i + j) & 1) ? isap.addflow(s, id[i][j], INF) : isap.addflow(id[i][j], t, INF);
        if (mp[i][j] == 'W') ((i + j) & 1) ? isap.addflow(id[i][j], t, INF) : isap.addflow(s, id[i][j], INF);
        if (i < n) {
            int w = ++cur, b = ++cur; sum += 2;
            isap.addflow(s, w, 1);
            isap.addflow(w, id[i][j], INF), isap.addflow(w, id[i + 1][j], INF);
            isap.addflow(b, t, 1);
            isap.addflow(id[i][j], b, INF), isap.addflow(id[i + 1][j], b, INF);
        }
        if (j < n) {
            int w = ++cur, b = ++cur; sum += 2;
            isap.addflow(s, w, 1);
            isap.addflow(w, id[i][j], INF), isap.addflow(w, id[i][j + 1], INF);
            isap.addflow(b, t, 1);
            isap.addflow(id[i][j], b, INF), isap.addflow(id[i][j + 1], b, INF);
        }
    } isap.init(t, 0, t);
    // printf("cur %d, S %d %d, sum %d\n", cur, s, t, sum);
    int maxflow = isap.calc();
    // printf("Maxflow %d\n", maxflow);
    cout << (sum - maxflow) << '\n';
    return 0;
}