#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

template<typename T>
inline void read(T &x) {
	register char c, f(0); x = 0;
	do if ((c = getchar()) == '-') f = true; while (isspace(c));
	do x = (x<<3) + (x<<1) + (c ^ 48), c = getchar(); while (isdigit(c));
	if (f) x = -x;
}
template <typename T, typename ...Args> inline void read(T &t, Args&... args) { read(t), read(args...); }

inline char getC() {
	register char c = getchar();
	while (c != 'm' && c != 'h') c = getchar();
	return c;
}

#define min(x, y) ((x)<(y)?(x):(y))

const int N = 200 + 7, M = 2000 + 7; 

std::vector<int> G[N];
int dfn[N], low[N], col[N], inq[N], q[N], qt(0), cdfn = 0, ccol = 0;
inline void add(int u, int v) {
	G[u].push_back(v);
}

inline void tarjan(int x) {
	dfn[x] = low[x] = ++cdfn;
	q[qt++] = x, inq[x] = true;
	
	for (const int &y : G[x]) {
		if (!dfn[y]) {
			tarjan(y), low[x] = min(low[x], low[y]);
		} else if (inq[y]) {
			low[x] = min(low[x], dfn[y]);
		}
	}
	
	if (dfn[x] == low[x]) {
		int y = ++ccol;
		do {
			y = q[--qt], col[y] = ccol, inq[y] = false;
		} while (x ^ y);
	}
}

inline bool proc() {
	int n, m, n2;
	read(n, m); n2 = (n<<1);
	
	cdfn = ccol = 0;
	for (int i(1); i <= n2; ++i) G[i].clear(), dfn[i] = low[i] = col[i] = 0;
	
	char t1, t2; int x, y;
	for (int i(1); i <= m; ++i) {
		t1 = getC(), read(x), t2 = getC(), read(y);
		// origin is 'h', +n is 'm'
		if (t1 == 'm' && t2 == 'm') {
			add(x, y + n), add(y, x + n);
		} else if (t1 == 'm' && t2 == 'h') {
			add(x, y), add(y + n, x + n);
		} else if (t1 == 'h' && t2 == 'm') {
			add(x + n, y + n), add(y, x);
		} else  if (t1 == 'h' && t2 == 'h') {
			add(x + n, y), add(y + n, x);
		}
	}
	
	
	for (int i(1); i <= n2; ++i) {
		if (!dfn[i]) tarjan(i);
	}	
	
	for (int i(1); i <= n; ++i) {
		if (col[i] == col[i + n]) return false;
	}
	return true;
}

int main() {
	int k;
	read(k);
	while (k--) {
		if (proc()) puts("GOOD");
		else puts("BAD");
	}
}
