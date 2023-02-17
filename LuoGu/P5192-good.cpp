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

const int N(5e5), INF(0x5FFFFFFF);

#define min(a, b) ((a)<(b) ? (a) : (b))

class ISAP {
private:
	struct Edge {
		int to; size_t rev; Data flow;
		Edge(int to, size_t rev, Data flow) : to(to), rev(rev), flow(flow) {}
	};
	
	int s, t;
	int n, m;
	std::vector<Edge> G[N];
	std::vector<int> dep, gap, now;
public:
	inline void clear(int n) {
		this->n = n;
		for (int i = 0; i ^ n; ++i) G[i].clear();
	}
	
	inline void add(int u, int v, Data f) {
		// printf("Add %d -> %d (f %d)\n", u, v, f);
		G[u].push_back(Edge(v, G[v].size(), f));
		G[v].push_back(Edge(u, G[u].size() - 1, 0));
	}
	
	inline void init() {
		// std::fill(dep.begin(), dep.begin() + n, -1), std::fill(gap.begin(), gap.begin() + n + n, 0);
		dep.assign(n, -1), gap.assign((n<<1), 0);
		
		std::queue<int> q; q.push(t);
		dep[t] = 0, gap[0] = 1;
		
		int x, y;
		while (q.size()) {
			x = q.front(); q.pop();
			for (auto &e : G[x]) {
				if (dep[(y = e.to)] == -1) {
					++gap[(dep[y] = dep[x] + 1)], q.push(y);
				}
			}
		} // end bfs
		
		// for (int i = 0; i < n; ++i) printf("Dep[%d] = %d\n", i, dep[i]);
	}
	
	inline Data sap(int x, Data flow) {
		// printf("In %d (flow %d)\n", x, flow);
		if (x == t) return flow;
		Data rest(flow), f;
		std::vector<Edge> & gx = G[x];
		int y, siz = gx.size();
		// printf("At x: %d\n");
		for (int & i = now[x]; i < siz; ++i) {
			Edge & e = gx[i];
			if (dep[(y = e.to)] + 1 == dep[x] && e.flow) {
				f = sap(y, min(rest, e.flow));
				if (f) {
					rest -= f, e.flow -= f;
					G[e.to][e.rev].flow += f;
				}
				if (!rest) return flow;
			}
		}
		
		if (--gap[dep[x]] == 0) dep[s] = n + 1;
		++gap[++dep[x]];
		return flow - rest;
	}
	
	inline Data calc(int s, int t) {
		this->s = s, this->t = t;
		// printf("Calc %d -> %d (n = %d)\n", s, t, n);
		this->init();
		
		Data maxflow(0);
		while (dep[s] <= n) {
			// std::fill(now.begin(), now.begin() + n, 0);
			now.assign(n, 0);
			maxflow += sap(s, INF);
		}
		return maxflow;
	}
	
	inline bool check(int s) {
		for (auto &e : G[s]) {
			if (e.flow) return true;
		}
		return false;
	}
	
	inline Data remove() {
		Data flow(0);
		for (auto &e : G[t]) {
			if (e.to == s) {
				flow += e.flow;
				e.flow = G[e.to][e.rev].flow = 0;
			}
		}
		return flow;
	}
};

static std::vector<int> in, out;
inline void proc(int n, int m) {
	static ISAP isap; // diff graph
	
	int tot = n + m + 4;
	isap.clear(tot);
	// std::fill(in.begin(), in.begin() + tot, 0), std::fill(out.begin(), out.begin() + tot, 0);
	in.assign(tot, 0), out.assign(tot, 0);
	
	for (int x = 0; x ^ tot; ++x) {
		in[x] = out[x] = 0;
	}
	// true in and out, fake in and out
	std::array<int, 2> tr = {n + m, n + m + 1}, fk = {n + m + 2, n + m + 3};
	
	// read in to person
	int g;
	for (int i = 0; i < m; ++i) {
		read(g);
		isap.add(tr[0], i, INF);
		in[i] += g, out[tr[0]] += g;
	}
	// printf("Read in to person ok !\n");
	
	// read every day (day node start from m)
	int c, d;
	for (int i = 0; i < n; ++i) {
		read(c, d);
		// printf("Reading day %d: c = %d, d = %d\n", i, c, d);
		isap.add(i + m, tr[1], d);
		// out[i + m] += d, in[tr[1]] += d;
		
		for (int t, l, r, j(0); j < c; ++j) {
			read(t, l, r);
			isap.add(t, i + m, r - l);
			out[t] += l, in[i + m] += l;
		}
	}
	
	// printf("Building fake roads\n");
	// build fake roads
	for (int i = 0; i ^ fk[0]; ++i) {
		if (in[i] > out[i]) {
			isap.add(fk[0], i, in[i] - out[i]);
		} else if (in[i] < out[i]) {
			isap.add(i, fk[1], out[i] - in[i]);
		}
	}
	// connect s to t
	isap.add(tr[1], tr[0], INF);
	
	// printf("Read and build ok\n");
	
	isap.calc(fk[0], fk[1]);
	if (isap.check(fk[0])) {
		printf("-1\n\n");
		return;
	}
	
	Data flow = isap.remove();
	flow += isap.calc(tr[0], tr[1]);
	printf("%d\n\n", flow);
}

int main() {
	int n, m;
	while (~scanf("%d %d", &n, &m)) {
		proc(n, m);
	}
	return 0;
}	 