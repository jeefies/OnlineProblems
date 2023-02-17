#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

const int N = 5e5 + 7, INF = 0x3F5F7F9F;
typedef int data;

inline int readInt() {
	char tmp; int x = 0, f = 1;
	do { if ((tmp = getchar()) == '-') f = -1; } while (tmp < '0' || tmp > '9');
	do { x = x * 10 + tmp - '0', tmp = getchar(); } while ('0' <= tmp && tmp <= '9');
	return x * f;
}

inline data max(data a, data b) {
	return a > b ? a : b;
}

inline data min(data a, data b) {
	return a < b ? a : b;
}

int n, m;
int def[N]; // vali
int oldRoot, root;

struct Edge {
	int to, next;
} edge[N]; int head[N], tot = 0;
inline void add(int u, int v) {
	edge[++tot] = {v, head[u]}, head[u] = tot;
}

void read() {
	n = readInt(), m = readInt();
	int u, v;
	for (int i = 1; i < n; ++i) {
		u = readInt(), v = readInt();
		add(u, v), add(v, u);
	}
	
	for (int i = 1; i <= n; ++i) def[i] = readInt();
	oldRoot = root = readInt();
}

int dfn[N], dep[N], siz[N], son[N], fa[N], top[N], cdfn = 0;
inline void workSSDF(int x, int par) {
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

inline void workDT(int x, int ptop) {
	dfn[x] = ++cdfn, top[x] = ptop;
	if (son[x]) workDT(son[x], ptop);
	
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (!dfn[y]) workDT(y, y); 
	}
}

typedef int data;
namespace seg {
	data origin[N];
	struct SegTree {
		int lte, rte, li, ri;
		data mi, lazy;
		void init(int l, int r) {
			li = l, ri = r;
		}
	} tree[N * 4];
	
	#define ct tree[p]
	#define lp 2*p
	#define rp 2*p+1
	#define lt tree[lp]
	#define rt tree[rp]
	
	inline void sync(int p) {
		if (ct.lazy) {
			rt.lazy = lt.lazy = rt.mi = lt.mi = ct.lazy;
			ct.lazy = 0;
		}
	}
	inline void update(int p) {
		ct.mi = min(lt.mi, rt.mi);
	}
	inline void build(int p) {
		if (ct.li == ct.ri) {
			ct.mi = origin[ct.li];
			return;
		}
		
		int mid = (ct.li + ct.ri) >> 1;
		lt.init(ct.li, mid), rt.init(mid + 1, ct.ri);
		build(lp), build(rp);
		update(p);
	}
	void build() {
		for (int i = 1; i <= n; ++i)
			origin[dfn[i]] = def[i];
		tree[1].init(1, n);
		build(1);
	}
	
	inline void change(int p, int l, int r, data val) {
		if (l <= ct.li && ct.ri <= r) {
			ct.mi = ct.lazy = val;
			return;
		}
		sync(p);
		int mid = (ct.li + ct.ri) >> 1;
		if (l <= mid) change(lp, l, r, val);
		if (mid < r)  change(rp, l, r, val);
		update(p);
	}
	void change(int l, int r, data val) {
		change(1, l, r, val);
	}
	
	inline void query(int p, int l, int r, data & res) {
		if (l <= ct.li && ct.ri <= r) {
			res = min(res, ct.mi);
			return;
		}
		sync(p);
		int mid = (ct.li + ct.ri) >> 1;
		if (l <= mid) query(lp, l, r, res);
		if (mid < r)  query(rp, l, r, res);
		return;
	}
	
	data query(int l, int r) {
		// printf("In querying [%d, %d]:\n", l, r);
		data ans = 1 << 30;
		query(1, l, r, ans);
		// printf("Out with ans %d\n", ans);
		return ans;
	}
}


int mark[N]; // in the path root <-> oldRoot
inline void changeRoot(int x) {
	root = x;
}

inline data simplequery(int x) {
	return seg::query(dfn[x], dfn[x] + siz[x] - 1);
}

inline int getPathSon(int rot, int x) {
	while (top[rot] != top[x]) {
		if (fa[top[rot]] == x) return top[rot];
		rot = fa[top[rot]];
	}
	return son[x];
}

int globalMin;
inline data query(int x) {
	// x is root or x has no relation to root.
	if (x == root) return seg::query(1, n);
	if (dfn[root] < dfn[x] || dfn[root] >= dfn[x] + siz[x]) {
		return simplequery(x);
	}

	// root is son of x
	// special process
	int now = getPathSon(root, x);
	data ans = 1 << 30;
	seg::query(1, 1, dfn[now] - 1, ans);
	if (dfn[now] + siz[now] <= n) seg::query(1, dfn[now] + siz[now], n, ans);
	return ans;
}

void wipe() {
	int x = readInt(), y = readInt(), v = readInt();
	while (top[x] != top[y]) {
		if (dep[top[x]] > dep[top[y]]) {
			seg::change(dfn[top[x]], dfn[x], v); x = fa[top[x]];
		} else {
			seg::change(dfn[top[y]], dfn[y], v); y = fa[top[y]];
		}
	}
	
	if (dfn[x] > dfn[y]) std::swap(x, y);
	seg::change(dfn[x], dfn[y], v);
}

int main() {
	read();
	workSSDF(root, 0), workDT(root, root);
	
	seg::build();
	
	int opt;
	for (int i = 1; i <= m; ++i) {
		opt = readInt();
		
		if (opt == 3) {
			printf("%d\n", query(readInt()));
		} else if (opt == 2) {
			wipe();
		} else if (opt == 1) {
			changeRoot(readInt());
		}
	}
	
	return 0;
}

/*
9 11
1 2
1 3
3 4
3 5
3 7
4 8
8 9
5 6
5 7 6 4 2 10 7 6 8
1
1 2
1 8
3 5
3 3
3 1
1 1
3 3
3 1
2 5 8 9
3 3
3 8
*/
/*
2
2
5
2
2
7
8
*/
/*
7 10
1 2
1 6
1 7
2 3
3 4
3 5
10 4 7 5 8 6 3
1
3 1
3 2
3 3
1 2
3 1
3 2
3 3
*/
/*
3
4
5
3
3
5
*/