#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

const int N = 1e5 + 7;

struct Edge {
	int to, next;
} edge[N];
int head[N], etot = 0;

void add(int u, int v) {
	edge[++etot] = {v, head[u]}, head[u] = etot;
}

int n, q;
int root[N], w[N], c[N];

void read() {
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", w + i, q + i);
	}
	
	int u, v;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &u, &v);
		add(u, v), add(v, u);
	}
}

int son[N], siz[N], dep[N], fa[N];
void workSSDF(int x, int par) {
	dep[x] = dep[par] + 1, fa[x] = par;
	siz[x] = 1;
	
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y == par) continue;
		workSSDF(y, x);
		siz[x] += siz[y];
		if (siz[y] > siz[son[x]]) son[x] = y;
	}
}
int dfn[N], top[N], cdfn = 0;
void workDT(int x, int ptop) {
	dfn[x] = ++cdfn, top[x] = ptop;
	if (son[x]) workDT(son[x], ptop);
	
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y == fa[x]) continue;
		workDT(y, y);
	}
}