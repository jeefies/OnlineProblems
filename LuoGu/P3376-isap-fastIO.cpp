#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <stack>
#include <deque>

typedef unsigned int uint;
namespace fastIO {
	const uint BUF_LEN = 1<<17|1;
	char buf[BUF_LEN], *ps = buf, *pe = buf;
	FILE * fp = stdin;
	
	inline void open(const char * fn) {
		fp = fopen(fn, "rb");
	}
	
	#define gc() (ps == pe && (pe = (ps = buf) + fread(buf, 1, BUF_LEN, fp), pe == ps) ? EOF : *ps++)
	template <typename T>
	inline void read(T &x) {
		register char tmp, f(0); x = 0;
		do if ((tmp = gc()) == '-') f = 1; while (tmp < '0' || '9' < tmp);
		do x = (x<<1) + (x<<3) + (tmp ^ 48), tmp = gc(); while ('0' <= tmp && tmp <= '9');
		if (f) x = -x;
	}
	template <typename T, typename ...Args>
	inline void read(T &x, Args&... args) {
		read(x), read(args...);
	}
};
using fastIO::read;

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
	
	// vector< vector<Edge> > v;
	vector<Edge> v[N * 2];
	
	ISAP(int n, int m, int s, int t) : n(n), m(m), s(s), t(t) {
		input();
	} 
	
	inline void input() {
		// v.resize(n + 1);
		for (int x, y, f, i(0); i ^ m; ++i) {
			read(x, y, f);
			v[x].push_back(Edge(y, v[y].size(), f));
			v[y].push_back(Edge(x, v[x].size() - 1, 0));
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
			for (auto &e : v[x]) {
				if (dep[(y = e.to)] == -1) // if dep[y] != -1
					++gap[(dep[y] = dep[x] + 1)], q[qt++] = y;
			}
		} // bfs end
	}
	
	inline Data sap(int x, Data flow) {
		if (x == t) return flow;
		
		Data rest = flow;
		int y, f;
		for (auto &e : v[x]) {
			if (dep[(y = e.to)] + 1 == dep[x] && e.flow) {
				f = sap(y, min(e.flow, rest));
				if (f) {
					e.flow -= f, v[e.to][e.rev].flow += f;
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
		Data maxflow(0), flow(0);
		static const Data INF(numeric_limits<Data>::max());
		// while (flow = sap(s, INF)) maxflow += flow;
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