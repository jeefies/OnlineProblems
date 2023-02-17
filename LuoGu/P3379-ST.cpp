#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

const int N = 5e5 + 7;

struct Edge {
	int to, next;
} edge[N * 2];
int head[N], tot = 0;

void add(int u, int v) {
	++tot;
	edge[tot] = {v, head[u]}, head[u] = tot;
}

int Log2[N];
int n, q, root, t;

int readInt() {
	char tmp;
	int x = 0, f = 1;
	do {
		if ((tmp = getchar()) == '-') f = -1;
	} while (tmp < '0' || tmp > '9');
	do {
		x = x * 10 + tmp - '0';
		tmp = getchar();
	} while ('0' <= tmp && tmp <= '9');
	return x * f;
}

void read() {
	n = readInt(), q = readInt(), root = readInt();
	
	int u, v;
	for (int i = 1; i < n; ++i) {
		u = readInt(); v = readInt();
		add(u, v), add(v, u);
	}
}

int st[N][21];
int dfn[N], rdfn[N], dep[N], fa[N], cdfn = 0;
void pre(int x, int par) {
	dfn[x] = ++cdfn, rdfn[cdfn] = x;
	dep[x] = dep[par] + 1;
	fa[x] = par;
	int y;
	for (int i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y != par) pre(y, x);
	}
}

int Max(int x, int y) {
	return dep[x] < dep[y] ? x : y;
}

void preST() {
	for (int i = 2; i <= n; ++i) Log2[i] = Log2[i >> 1] + 1;
	t = Log2[n];
	
	for (int i = 1; i <= n; ++i) st[i][0] = rdfn[i];
	
	for (int k = 1; k <= t; ++k) {
		for (int i = 1; i + (1<<k) - 1 <= n; ++i)
			st[i][k] = Max(st[i][k-1], st[i + (1 << (k-1))][k-1]);
	}
}

int query(int l, int r) {
	int k = Log2[r - l + 1];
	return Max(st[l][k], st[r - (1<<k) + 1][k]);
}

int main() {
	read();
	pre(root, 0);
	preST();
	int x, y;
	while (q--) {
		x = readInt(), y = readInt();
		if (x == y) {
			printf("%d\n", x);
		} else {
			if (dfn[x] > dfn[y]) std::swap(x, y);
			printf("%d\n", fa[query(dfn[x] + 1, dfn[y])]);
		}
	}
	return 0;
}