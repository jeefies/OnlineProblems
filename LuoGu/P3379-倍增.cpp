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

// int Log2[N];
int n, q, root, t;
int dep[N], fa[N][21];

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

void pre(int x, int par) {
	dep[x] = dep[par] + 1;
	fa[x][0] = par;
	for (int i = 1; i <= t; ++i) fa[x][i] = fa[fa[x][i - 1]][i - 1];
	
	int y;
	for (int i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y != par) {
			pre(y, x);
			// printf("Pre %d (fa %d) ok\n", y, x);
		}
	}
}

int lca(int x, int y) {
	int p;
	if (dep[x] < dep[y]) p = x, x = y, y = p;
	
	p = 0;
	while (p >= 0) {
		if (dep[fa[x][p]] >= dep[y]) x = fa[x][p], ++p;
		else --p;
	}
		
	if (x == y) return x;
	
	p = 0;
	while (p >= 0) {
		if (fa[x][p] != fa[y][p]) x = fa[x][p], y = fa[y][p], ++p;
		else --p;
	}
	return fa[x][0];
}

void work() {
	int x, y;
	while (q--) {
		x = readInt(), y = readInt();
		// printf("LCA %d, %d\n", x, y);
		printf("%d\n", lca(x, y));
	}
}

int main() {
	read();
	// printf("Read OK\n");
	pre(root, 0);
	// printf("Pre work OK\n");
	work();
	return 0;
}