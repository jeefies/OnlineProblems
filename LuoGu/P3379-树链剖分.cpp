#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

const int N = 5e5 + 7;

struct Edge {
	int to, next;
} edge[N * 2];
// typedef struct Edge Edge;
int head[N], tot = 0;

void add(int u, int v) {
	++tot;
	edge[tot] = {v, head[u]}, head[u] = tot;
}

int readInt() {
	char tmp;
	int x = 0, f = 1;
	do {
		tmp = getchar();
		if (tmp == '-') f = -1;
	} while (tmp < '0' || tmp > '9');
	do {
		x = x * 10 + tmp - '0';
		tmp = getchar();
	} while ('0' <= tmp && tmp <= '9');
	return x * f;
}

int n, q, root, t;
void read() {
	n = readInt(), q = readInt(), root = readInt();
	
	// for (int i = 2; i <= n; ++i) Log2[i] = Log2[i >> 1] + 1;
	// t = Log2[n];
	t = log(n) / log(2) + 1;
	
	int u, v;
	for (int i = 1; i < n; ++i) {
		u = readInt(); v = readInt();
		add(u, v), add(v, u);
	}
}

int top[N], dfn[N], son[N], dep[N], siz[N], fa[N];
// work son, siz and dep
void workSSDF(int x, int par) {
	dep[x] = dep[par] + 1, fa[x] = par;
	siz[x] = 1;
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y == par) continue;
		workSSDF(y, x);
		siz[x] += siz[y];
		if (siz[y] >= siz[son[x]]) son[x] = y;
	}
}

// work dfn and top
int cdfn = 0;
void workDT(int x, int par, int ptop) {
	dfn[x] = ++cdfn, top[x] = ptop;
	if (son[x]) workDT(son[x], x, top[x]);
	
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y == par || y == son[x]) continue;
		workDT(y, x, y);
	}
}

int lca(int x, int y) {
	while (top[x] != top[y]) {
		// make deeper top jump
		if (dep[top[x]] >= dep[top[y]]) x = fa[top[x]];
		else y = fa[top[y]];
	}
	// now, top[x] == top[y], return which dep is smaller
	if (dep[x] <= dep[y]) return x;
	return y;
}

int main() {
	read();
	workSSD(root, 0);
	workDT(root, 0, root);
	int x, y;
	while (q--) {
		x = readInt(), y = readInt();
		printf("%d\n", lca(x, y));
	}
	return 0;
}