#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

const int N = 5e5 + 7, MOD = 1e9 + 7;

inline int readInt() {
	char tmp; int x = 0, f = 1;
	do { if ((tmp = getchar()) == '-') f = -1; } while (tmp < '0' || tmp > '9');
	do { x = x * 10 + tmp - '0', tmp = getchar(); } while ('0' <= tmp && tmp <= '9');
	return x * f;
}

int n, q;

typedef int data;

inline data max(data a, data b) {
	return a > b ? a : b;
}

namespace seg {
	struct SegTree {
		int l, r, lp, rp;
		data sum, lazy, ma;
	};
	SegTree tree[N * 4];
	#define il tree[p].l
	#define ir tree[p].r
	#define ct tree[p]
	#define lp ct.lp
	#define rp ct.rp
	#define lt tree[lp]
	#define rt tree[rp]
	
	
	int usage = 0;
	int newTree(int l, int r) {
		tree[++usage].l = l, tree[usage].r = r;
		return usage;
	}
	
	int root[N] = {0};
	inline int check(int id) {
		if (!root[id])
			root[id] = newTree(1, n);
		return root[id];
	}
	
	inline void update(int p) {
		ct.sum = (lt.sum + rt.sum);
		ct.ma = max(lt.ma, rt.ma);
	}
	
	void change(int p, int i, data val) {
		// printf("In [%d, %d] (p %d) changing %d to %d\n", il, ir, p, i, val);
		if (il == i && i == ir) {
			ct.sum = ct.ma = val;
			return;
		}
		
		int mid = (il + ir) >> 1;
		if (i <= mid) {
			if (!lp) lp = newTree(il, mid);
			change(lp, i, val);
		}
		
		if (mid < i) {
			if (!rp) rp = newTree(mid + 1, ir);
			change(rp, i, val);
		}
		
		update(p);
	}
	
	data query(int p, int tl, int tr, int &ma) {
		if (tl <= il && ir <= tr) {
			ma = max(ma, ct.ma);
			return ct.sum;
		}
		
		int mid = (il + ir) >> 1;
		
		data ans = 0;
		if (lp && tl <= mid) ans = query(lp, tl, tr, ma);
		if (rp && mid < tr) ans += query(rp, tl, tr, ma);
		return ans;
	}
}

struct Edge {
	int to, next;
};
Edge edge[N];
int head[N], tot = 0;

inline void add(int u, int v) {
	edge[++tot] = {v, head[u]}, head[u] = tot;
}

int w[N], c[N], root;

void read() {
	n = readInt(), q = readInt();
	for (int i = 1; i <= n; ++i) {
		w[i] = readInt(), c[i] = readInt();
	}
	root = (1 + n) / 2;
	
	int u, v;
	for (int i = 1; i < n; ++i) {
		u = readInt(), v = readInt();
		add(u, v), add(v, u);
	}
}

int dep[N], siz[N], son[N], fa[N], top[N], dfn[N], cdfn = 0;
void workSSDF(int x, int par) {
	dep[x] = dep[par] + 1, siz[x] = 1, fa[x] = par;
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y == par) continue;
		workSSDF(y, x);
		siz[x] += siz[y];
		if (siz[y] > siz[son[x]]) son[x] = y;
	}
}

inline void workDT(int x, int ptop) {
	dfn[x] = ++cdfn, top[x] = ptop;
	if (son[x]) workDT(son[x], ptop);
	
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (!dfn[y]) workDT(y, y);
	}
}

inline void procChange() {
	char tmp = getchar();
	int x = readInt(), v = readInt();
	// data sum, ma = 0;
	if (tmp == 'C') {
		// change root
		// old root c[x] => v
		seg::change(seg::check(c[x]), dfn[x], 0);
		seg::change(seg::check(c[x] = v), dfn[x], w[x]);
	} else {
		seg::change(seg::check(c[x]), dfn[x], w[x] = v);
	}
}

inline void procQuery() {
	char tmp = getchar();
	int x = readInt(), y = readInt();
	int rg = seg::check(c[x]);
	data sum = 0, ma = 0;
	
	while (top[x] != top[y]) {
		// jump lower one
		if (dep[top[x]] < dep[top[y]]) sum += seg::query(rg, dfn[top[y]], dfn[y], ma), y = fa[top[y]];
		else sum += seg::query(rg, dfn[top[x]], dfn[x], ma), x = fa[top[x]];
	}
	if (dfn[x] > dfn[y]) sum += seg::query(rg, dfn[y], dfn[x], ma);
	else sum += seg::query(rg, dfn[x], dfn[y], ma);
	
	if (tmp == 'S') printf("%d\n", sum);
	else printf("%d\n", ma);
}

int main() {
	read();
	workSSDF(root, 0);
	workDT(root, root);
	
	/*
	printf("root: %d\n", root);
	for (int i = 1; i <= n; ++i) {
		printf("\tnode: %d\n", i);
		printf("\t\tdfn: %d, top: %d\n", dfn[i], top[i]);
	}
	*/
	
#define cityW w[i]
#define cityC c[i]
	for (int i = 1; i <= n; ++i) {
		seg::change(seg::check(cityC), dfn[i], cityW);
	}
	
	char tmp;
	while (q--) {
		do tmp = getchar(); while (tmp != 'C' && tmp != 'Q');
		if (tmp == 'C') procChange();
		else procQuery();
	}
	return 0;
}