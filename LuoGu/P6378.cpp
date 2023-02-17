#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <stack>
#include <deque>

template<typename T>
inline void read(T &x) {
	char c, f = 0; x = 0;
	do if ((c = getchar()) == '-') f = true; while (isspace(c));
	do x = (x<<3) + (x<<1) + (c ^ 48), c = getchar(); while (isdigit(c));
	if (f) x = -x;
}

template <typename T, typename ...Args> inline void read(T &t, Args&... args) { read(t), read(args...); }

using namespace std;

const int N = 4e6 + 7;
int n, m, k;
vector<int> G[N];

inline void add(int u, int v) {
	G[u].push_back(v);
}

int dfn[N], low[N], col[N], inq[N], cdfn = 0, ccol = 0;
int stk[N], top = 0;
inline void tarjan(int x) {
	dfn[x] = low[x] = ++cdfn;
	stk[top++] = x, inq[x] = true;
	for (const int &y : G[x]) {
		if (!dfn[y]) tarjan(y), low[x] = min(low[x], low[y]);
		else if (inq[y]) low[x] = min(low[x], dfn[y]);
	}
	
	if (low[x] == dfn[x]) {
		int y = ++ccol;
		do {
			y = stk[--top], inq[y] = false, col[y] = ccol;
		} while (y != x);
	}
}

int main() {
	read(n, m, k);
	// read(n), read(m), read(k);
	int pc = n * 2, sc = n * 3;
	
	int u, v;
	for (int i = 1; i <= m; ++i) {
		read(u, v);
		// read(u), read(v);
		add(u + n, v);
		add(v + n, u);
	}
	
	int w;
	for (int i = 1; i <= k; ++i) {
		read(w);
		for (int j = 1; j <= w; ++j) {
			// pc: Ç°×º£¬scºó×º 
			read(u), ++pc, ++sc;
			add(pc, u + n), add(sc, u + n);
			if (j ^ 1) add(u, pc - 1), add(pc, pc - 1);
			if (j ^ w) add(u, sc + 1), add(sc, sc + 1);
		}
	}
	
	for (int i = 1; i <= (n << 2); ++i) {
		if (!dfn[i]) tarjan(i); 
	}
	
	for (int i = 1; i <= n; ++i) {
		if (col[i] == col[i + n]) return puts("NIE"), 0;
	}
	return puts("TAK"), 0;
} 
