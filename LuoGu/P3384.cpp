#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

const int N = 1e5 + 7;

struct Edge {
	int to, next;
} edge[N * 2];
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

int n, q, root, mod;
int a[N], b[N];
void read() {
	n = readInt(), q = readInt(), root = readInt(), mod = readInt();
	for (int i = 1; i <= n; ++i) {
		b[i] = readInt();
	}
	int u, v;
	for (int i = 1; i < n; ++i) {
		u = readInt(), v = readInt();
		add(u, v), add(v, u);
	}
}

int dfn[N], dep[N], fa[N], son[N], siz[N], top[N], cdfn = 0;
// work depth, father, son, size
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
void workDT(int x, int par, int ptop) {
	top[x] = ptop, dfn[x] = ++cdfn;
	if (son[x]) workDT(son[x], x, ptop);
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y == par || y == son[x]) continue;
		workDT(y, x, y);
	}
}

// SegmentTree !!!!! damn it
struct SegTree {
	long long len, sum, add;
};
SegTree tree[4 * N];
#define lt tree[p*2]
#define rt tree[p*2 + 1]
#define ct tree[p]

void sync(int p) {
	if (ct.add) {
		lt.sum = (lt.sum + lt.len * ct.add) % mod;
		lt.add = (lt.add + ct.add) % mod;
		
		rt.sum = (rt.sum + rt.len * ct.add) % mod;
		rt.add = (rt.add + ct.add) % mod;
		ct.add = 0;
	}
}

void build(int p, int l, int r) {
	ct.len = r - l + 1;
	if (l == r) {
		ct.sum = a[l] % mod;
		return;
	}
	
	int mid = (l + r) >> 1;
	build(p*2, l, mid);
	build(p*2 + 1, mid + 1, r);
	ct.sum = (lt.sum + rt.sum) % mod;
}

void modify(int p, int l, int r, int tl, int tr, int val) {
	if (tl <= l && r <= tr) {
		ct.sum = (ct.sum + ct.len * val) % mod;
		ct.add = (ct.add + val) % mod;
		return;
	}
	
	sync(p);
	
	int mid = (l + r) >> 1;
	if (tl <= mid) modify(p*2, l, mid, tl, tr, val);
	if (tr > mid) modify(p*2 + 1, mid + 1, r, tl, tr, val);
	ct.sum = (lt.sum + rt.sum) % mod;
}

long long query(int p, int l, int r, int tl, int tr) {
	if (tl <= l && r <= tr) {
		return ct.sum % mod;
	}
	
	sync(p);
	int mid = (l + r) >> 1;
	long long ans = 0;
	if (tl <= mid) ans = query(p * 2, l, mid, tl, tr) % mod;
	if (tr > mid) ans += query(p*2 + 1, mid + 1, r, tl, tr);
	return ans % mod;
}

void addPath() {
	int x = readInt(), y = readInt(), z = readInt() % mod;
	
	// not in same line
	while (top[x] != top[y]) {
		if (dep[top[x]] > dep[top[y]]) {
			// jump x
			modify(1, 1, n, dfn[top[x]], dfn[x], z);
			x = fa[top[x]];
		} else {
			// jump y
			modify(1, 1, n, dfn[top[y]], dfn[y], z);
			y = fa[top[y]];
		}
	}
	
	// in same line
	// make sure dfn[x] <= dfn[y]
	if (dfn[x] > dfn[y]) std::swap(x, y);
	modify(1, 1, n, dfn[x], dfn[y], z);
}

void queryPath() {
	int x = readInt(), y = readInt();
	long long ans = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] > dep[top[y]]) {
			// jump x
			ans = (ans + query(1, 1, n, dfn[top[x]], dfn[x])) % mod;
			x = fa[top[x]];
		} else {
			// jump y
			ans = (ans + query(1, 1, n, dfn[top[y]], dfn[y])) % mod;
			y = fa[top[y]];
		}
	}
	
	if (dfn[x] > dfn[y]) std::swap(x, y);
	ans = (ans + query(1, 1, n, dfn[x], dfn[y])) % mod;
	printf("%lld\n", ans);
}

void addTree() {
	int x = readInt(), z = readInt() % mod;
	modify(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, z);
}

void queryTree() {
	int x = readInt();
	long long ans = query(1, 1, n, dfn[x], dfn[x] + siz[x] - 1);
	printf("%lld\n", ans);
}

int main() {
	read();
	workSSDF(root, 0);
	workDT(root, 0, root);
	for (int i = 1; i <= n; ++i) {
		a[dfn[i]] = b[i];
	} build(1, 1, n);
	
	while (q--) {
		switch(readInt()) {
			case 1: addPath(); break;
			case 2: queryPath(); break;
			case 3: addTree(); break;
			case 4: queryTree(); break;
		}
	}
	return 0;
}