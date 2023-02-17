#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <stack>
#include <deque>

template<typename T>
inline void read(T &x) {
	char c, f(0); x = 0;
	do if ((c = getchar()) == '-') f = true; while (isspace(c));
	do x = (x<<3) + (x<<1) + (c ^ 48), c = getchar(); while (isdigit(c));
	if (f) x = -x;
}
template <typename T, typename ...Args> inline void read(T &t, Args&... args) { read(t), read(args...); }

typedef long long Data;
using namespace std;

const int N = 207, M = 5007;

struct Edge {
	int to;
	size_t rev;
	Data flow;
	Edge(int to, size_t rev, Data f) : to(to), rev(rev), flow(f) {}
};

class ISAP {
public:
	int n, m, s, t;
	vector<int> dep;
	int q[N * 2], gap[N * 2];
	
	// vector< vector<Edge> > G;
	deque<Edge> G[N * 2];
	
	ISAP(int n, int m, int s, int t) : n(n), m(m), s(s), t(t) {
		input();
	}
	
	inline void addflow(int u, int v, Data f) {
		// printf("From %d -> %d f %d\n", u, v, f);
		G[u].push_back(Edge(v, G[v].size(), f));
		G[v].push_back(Edge(u, G[u].size() - 1, 0));
	}
	
	inline void input() {
		// G.resize(n + 1);
		for (int x, y, f, i(0); i ^ m; ++i) {
			read(x, y, f);
			addflow(x, y, f);
		}
	}
	
	inline void init() {
		dep.assign(n + 1, -1);
		dep[t] = 0, gap[0] = 1;
		
		register int qt(0), qf(0);
		q[qt++] = t;
		int x, y;
		while (qf ^ qt) {
			x = q[qf++];
			for (auto &e : G[x]) {
				if (dep[(y = e.to)] == -1) // if dep[y] != -1
					++gap[(dep[y] = dep[x] + 1)], q[qt++] = y;
			}
		} // bfs end
	}
	
	inline Data sap(int x, Data flow) {
		if (x == t) return flow;
		
		Data rest = flow;
		int y, f;
		for (auto &e : G[x]) {
			if (dep[(y = e.to)] + 1 == dep[x] && e.flow) {
				f = sap(y, min(e.flow, rest));
				if (f) {
					e.flow -= f, G[e.to][e.rev].flow += f;
					rest -= f;
				}
				if (!rest) return flow; // flow all used
			}
		}
		
		// change dep
		if (--gap[dep[x]] == 0) dep[s] = n + 1; // can not reach to t
		++gap[++dep[x]]; // ++depth
		return flow - rest;
	}
	
	inline Data calc() {
		Data maxflow(0);
		static const Data INF(numeric_limits<Data>::max());
		while (dep[s] <= n) maxflow += sap(s, INF);
		return maxflow;
	}
};

int main() {
	int n, m, s, t;
	read(n, m, s, t);
	
	static ISAP isap(n, m, s, t);
	isap.init();
	printf("%lld\n", isap.calc());
	
	return 0;
}
