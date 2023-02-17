#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <stack>
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

typedef long long Data;
// using namespace std;

const int N = 1e4 + 7;

#define min(a, b) ((a)<(b) ? (a) : (b))

class ISAP {
private:
	struct Edge {
		int to; size_t rev; Data flow;
		Edge(int to, size_t rev, Data flow) : to(to), rev(rev), flow(flow) {}
	};
	
	int s, t;
	int a, b, c;
	std::array<int, 4> fro;
	std::vector<Edge> G[N * 4];
	std::vector<int> dep;
	int gap[N * 6], q[N * 6];
	
public:
	ISAP(int a, int b, int c) : a(a), b(b), c(c) {
		s = 0, t = a + b + c + a + 1;
		input();
		init();
	}
	
	inline void addflow(int u, int v, Data f) {
		// printf("From %d -> %d f %d\n", u, v, f);
		G[u].push_back(Edge(v, G[v].size(), f));
		G[v].push_back(Edge(u, G[u].size() - 1, 0));
	}
	
	inline void input() {
		int m, x, y;
		
		fro = {a + a, 0, a, a + a + b};
		
		read(m);
		// ce to left book
		for (int i(0); i < m; ++i) {
			read(x, y);
			addflow(y + fro[0], x + fro[1], 1);
		}
		
		// right book to ans
		read(m);
		for (int i(0); i < m; ++i) {
			read(x, y);
			addflow(x + fro[2], y + fro[3], 1);
		}
		
		// in to ce
		for (int i(1); i <= b; ++i)
			addflow(s, i + fro[0], 1);
		// left book to right book
		for (int i(1); i <= a; ++i)
			addflow(i, i + fro[2], 1);
		// ans to out
		for (int i(1); i <= c; ++i)
			addflow(i + fro[3], t, 1);
	}
	
	inline void init() {
		dep.assign(t + 1, -1);
		gap[0] = 1, dep[t] = 0;
		
		register int qf(0), qt(0), x, y;
		q[qt++] = t;
		while (qf ^ qt) {
			x = q[qf++];
			for (auto &e : G[x]) {
				if (dep[(y = e.to)] == -1)
					++gap[(dep[y] = dep[x] + 1)], q[qt++] = y;
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
	int a, b, c;
	read(a, b, c);
	
	static ISAP isap(a, b, c);
	printf("%lld\n", isap.calc());
	
	return 0;
}
