#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

const int N = 5e5 + 7, MOD = 201314;

int readInt() {
	char tmp; int x = 0, f = 1;
	do { if ((tmp = getchar()) == '-') f = -1; } while (tmp < '0' || tmp > '9');
	do { x = x * 10 + tmp - '0', tmp = getchar(); } while ('0' <= tmp && tmp <= '9');
	return x * f;
}

struct Edge {
	int to, next;
} edge[N * 2];
int head[N], tot = 0;
void add(int u, int v) {
	edge[++tot] = {v, head[u]}, head[u] = tot;
}

int n, m, root = 1;
int fa[N], siz[N], dfn[N], dep[N], top[N], son[N], cdfn = 0;

void read() {
	scanf("%d %d", &n, &m);
	int t;
	for (int i = 2; i <= n; ++i) {
		fa[i] = t = readInt() + 1;
		add(t, i);
	}
}

struct Ques {
	int l, z, f, i;
	bool operator< (const Ques & q) const {
		return l < q.l;
	}
} ques[N * 2];

int qn;
void readQues() {
	Ques * q = ques;
	int l, r, z;
	for (int i = 0; i < m; ++i) {
		l = readInt() + 1, r = readInt() + 1, z = readInt() + 1;
		*q = {l - 1, z, -1, i}; ++q;
		*q = {r, z, 1, i}; ++q;
	}
	
	qn = q - ques;
	std::sort(ques, q);
}

void workSSDF(int x) {
	dep[x] = dep[fa[x]] + 1, siz[x] = 1;
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		workSSDF(y);
		siz[x] += siz[y];
		if (siz[y] > siz[son[x]]) son[x] = y;
	}
}

void workDT(int x, int ptop) {
	top[x] = ptop, dfn[x] = ++cdfn;
	if (son[x]) workDT(son[x], ptop);
	
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y != son[x]) workDT(y, y);
	}
}

typedef long long data;
namespace seg {
	struct SegTree {
		int l, r, lp, rp;
		data sum, lazy;
	};
	SegTree tree[N * 4];
	#define il tree[p].l
	#define ir tree[p].r
	#define ct tree[p]
	#define lp ct.lp
	#define rp ct.rp
	#define lt tree[lp]
	#define rt tree[rp]
	
	void init(int n) {
		tree[1] = {1, n, 0, 0, 0, 0};
	}
	
	int usage = 1;
	int newTree(int l, int r) {
		tree[++usage].l = l, tree[usage].r = r;
		return usage;
	}
	
	void sync(int p) {
		if (ct.lazy) {
			lt.sum = (lt.sum + ct.lazy * (lt.r - lt.l + 1)) % MOD;
			lt.lazy = (lt.lazy + ct.lazy) % MOD;
			
			rt.sum = (rt.sum + ct.lazy * (rt.r - rt.l + 1)) % MOD;
			rt.lazy = (rt.lazy + ct.lazy) % MOD;
			ct.lazy = 0;
		}
	}
	
	void update(int p) {
		ct.sum = (lt.sum + rt.sum) % MOD;
	}
	
	void add(int p, int tl, int tr, data val) {
		// printf("\t\tAdding in [%d, %d] (p %d)\n", il, ir, p);
		if (tl <= il && ir <= tr) {
			ct.sum = (ct.sum + val * (ir - il + 1)) % MOD;
			ct.lazy = (ct.lazy + val) % MOD;
			return;
		}
		
		int mid = (il + ir) >> 1;
		if (!lp) lp = newTree(il, mid);
		if (!rp) rp = newTree(mid + 1, ir);
		sync(p);
		
		if (tl <= mid) add(lp, tl, tr, val);
		if (mid < tr)  add(rp, tl, tr, val);
		update(p);
	}
	
	data query(int p, int tl, int tr) {
		if (tl <= il && ir <= tr) {
			return ct.sum;
		}
		
		int mid = (il + ir) >> 1;
		if (!lp) lp = newTree(il, mid);
		if (!rp) rp = newTree(mid + 1, ir);
		sync(p);
		
		data ans = 0;
		if (tl <= mid) ans = query(lp, tl, tr) % MOD;
		if (mid < tr) ans += query(rp, tl, tr);
		return ans % MOD;
	}
}

void add(int x) {
	// printf("Add path %d -> root\n", x);
	while (top[x]) {
		// printf("\tModify [%d, %d]\n", dfn[top[x]], dfn[x]);
		seg::add(1, dfn[top[x]], dfn[x], 1);
		x = fa[top[x]];
	}
}

data query(int x) {
	// printf("Query %d to root: ", x);
	data ans = 0;
	while (top[x]) {
		ans = (ans + seg::query(1, dfn[top[x]], dfn[x])) % MOD;
		x = fa[top[x]];
	}
	// printf("%d\n", ans);
	return ans;
}

data res[N];

int main() {
	read();
	readQues();
	workSSDF(root); workDT(root, root);
	seg::init(n);
	
	int r = 0;
	Ques * q = ques;
	for (int i = 0; i < qn; ++i) {
		// printf("At query {%d, %d, %d, %d}\n", q->l, q->z, q->f, q->i);
		while (r < q->l) add(++r);
		res[q->i] = (res[q->i] + query(q->z) * q->f) % MOD;
		++q;
	}
	
	for (int i = 0; i < m; ++i) printf("%lld\n", (res[i] + MOD) % MOD);
	return 0;
}