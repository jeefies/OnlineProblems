#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <array>

template<typename T>
inline void read(T &x) {
	char c, f(0); x = 0;
	do if ((c = getchar()) == '-') f = true; while (isspace(c));
	do x = (x<<3) + (x<<1) + (c ^ 48), c = getchar(); while (isdigit(c));
	if (f) x = -x;
}
template <typename T, typename ...Args> inline void read(T &t, Args&... args) { read(t), read(args...); }

typedef int Data;
// using namespace std;

const int N = 1.5e6 + 7;

#define min(a, b) ((a)<(b) ? (a) : (b))
#define pos(i, j) ((i)*m+(j))

class ISAP {
private:
	struct Edge {
		int to; size_t rev; Data flow;
		Edge(int to, size_t rev, Data flow) : to(to), rev(rev), flow(flow) {}
	};
	
	int s, t;
	int n, m;
	std::vector<Edge> G[N];
	std::vector<int> dep;
	int gap[N];
	
public:
	ISAP(int n, int m) : n(n), m(m) {
		s = 0, t = pos(n - 1, m - 1);
		// printf("s %d, t %d\n", s, t);
		input();
		init();
	}
	
	inline void addflow(int u, int v, Data f) {
		// printf("From %d -> %d f %d\n", u, v, f);
		G[u].push_back(Edge(v, G[v].size(), f));
		G[v].push_back(Edge(u, G[u].size() - 1, f));
	}
	
	inline void input() {
		int w;
		register int i, j;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m - 1; ++j)
				read(w), addflow(pos(i, j), pos(i, j + 1), w);
		}
		
		for (i = 0; i < n - 1; ++i) {
			for (int j = 0; j < m; ++j)
				read(w), addflow(pos(i, j), pos(i + 1, j), w);
		}
		
		for (int i = 0; i < n - 1; ++i) {
			for (int j = 0; j < m - 1; ++j)
				read(w), addflow(pos(i, j), pos(i + 1, j + 1), w);
		}
	}
	
	inline void init() {
		dep.assign(n * m, -1);
		gap[0] = 1, dep[t] = 0;
		
		int x, y;
		// q[qt++] = t;
		std::queue<int> q; q.push(t);
		while (q.size()) {
			x = q.front(); q.pop();
			for (auto &e : G[x]) {
				if (dep[(y = e.to)] == -1)
					++gap[(dep[y] = dep[x] + 1)], q.push(y);
			}
		} // end bfs
	}
	
	inline Data sap(int x, Data flow) {
		if (x == t) return flow;
		Data rest(flow);
		int y, f;
		for (auto &e : G[x]) {
			if (dep[(y = e.to)] + 1 == dep[x] && e.flow) {
				f = sap(y, min(e.flow, rest));
				if (f) {
					e.flow -= f, G[e.to][e.rev].flow += f;
					rest -= f;
				}
				if (!rest) return flow;
			}
		}
		
		if (--gap[dep[x]] == 0) dep[s] = t + 1;
		++gap[++dep[x]];
		return flow - rest;
	}
	
	inline Data calc() {
		Data maxflow(0), INF(0x5FFFFFFF);
		while (dep[s] <= t) maxflow += sap(s, INF);
		return maxflow;
	}
};

int main() {
	int n, m;
	read(n, m);
	
	static ISAP isap(n, m);
	printf("%d\n", isap.calc());
	
	return 0;
}
