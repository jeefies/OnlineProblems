#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>

const int N = 4e4 + 7;

int readInt() {
	int n = 0, f = 1; char tmp;
	do { if ((tmp = getchar()) == '-') f = -1; } while (tmp < '0' || '9' < tmp);
	do { n = n * 10 + tmp - '0', tmp = getchar(); } while ('0' <= tmp && tmp <= '9');
	return n * f;
}

struct Op {
	int op, u, v;
} op[N], *q;
int n, m, root;

#define lowbit(i) (i & -i)
class BIT {
private:
	int b[N];
public:
	int query(int i) {
		int r = 0;
		while (i) r += b[i], i -= lowbit(i);
		return r;
	}
	void update(int i, int x) {
		while (i <= n) b[i] += x, i += lowbit(i);
	}
};

class MergeFindSet {
public:
	int grp[N];
	MergeFindSet(int n) {
		init(n);
	}
	void init(int n) {
		for (int i = 1; i <= n; ++i) grp[i] = i;
	}
	
	int find(int x) {
		if (x == grp[x]) return x;
		return grp[x] = find(grp[x]);
	}
	
	void merge(int x, int y) {
		grp[find(x)] = find(y);
	}
};

namespace tree {
	struct Edge {
		int to, next;
	} edge[N * 2];
	int head[N], tot = 0;
	int root;
	
	void add(int u, int v) {
		edge[++tot] = {v, head[u]}, head[u] = tot;
	}
	
	int dfn[N], siz[N], top[N], son[N], dep[N], fa[N], cdfn = 0;
	void workSSDF(int x, int par) {
		dep[x] = dep[par] + 1, fa[x] = par, siz[x] = 1;
		for (int y, i = head[x]; i; i = edge[i].next) {
			y = edge[i].to;
			if (y == par) continue;
			workSSDF(y, x);
			siz[x] += siz[y];
			if (siz[y] > siz[son[x]]) son[x] = y;
		}
	}
	
	void workDT(int x, int ptop) {
		dfn[x] = ++cdfn, top[x] = ptop;
		if (son[x]) workDT(son[x], ptop);
		
		for (int y, i = head[x]; i; i = edge[i].next) {
			y = edge[i].to;
			if (dfn[y]) continue;
			workDT(y, y);
		}
	}
	
	int getLCA(int x, int y) {
		while (top[x] != top[y]) {
			if (dep[top[x]] > dep[top[y]]) x = fa[top[x]];
			else y = fa[top[y]];
		}
		return dep[x] < dep[y] ? x : y;
	}
	
	static BIT bit;
	void mark(int x, int v) {
		// printf("node %d, [%d, %d) add %d\n", x, dfn[x], dfn[x] + siz[x], v);
		bit.update(dfn[x], v);
		bit.update(dfn[x] + siz[x], -v);
	}
	
	void preWork() {
		root = (1 + n) / 2;
		workSSDF(root, 0);
		workDT(root, root);
		// printf("root: %d\n", root);
		
		for (int i = 1; i <= n; ++i) {
			if (i ^ root) mark(i, 1);
		}
	}
	
	void modify(int x, int y) {
		static MergeFindSet mfs(n);
		int gx = mfs.find(x), gy = mfs.find(y), lca = getLCA(x, y);
		while (gx != gy) {
			// lower one first.
			if (dep[gx] < dep[gy]) std::swap(gx, gy);
			if (gx != lca) {
				mark(gx, -1);
			}
			gx = mfs.grp[gx] = mfs.find(fa[gx]);
		}
		// Ha?
	}
	
	int query(int x, int y) {
		return bit.query(dfn[x]) + bit.query(dfn[y]) - bit.query(dfn[getLCA(x, y)]) * 2;
	}
};

namespace origin {
	std::set<int> g[N];
	
	void add(int u, int v) {
		g[u].insert(v), g[v].insert(u);
	}
	
	void del(int u, int v) {
		g[u].erase(v), g[v].erase(u);
	}
	
	void toTree() {
		static int delx[N], dely[N], cnt = 0;
		static MergeFindSet mfs(n);
		for (int x = 1; x <= n; ++x) {
			cnt = 0;
			for (const int y : g[x]) {
				int gx = mfs.find(x), gy = mfs.find(y);
				// already merged
				if (gx == gy) continue; 
				mfs.merge(gx, gy);
				// mark del
				delx[cnt] = x, dely[cnt] = y, ++cnt;
				tree::add(x, y), tree::add(y, x);
			}
			while (cnt--) {
				del(delx[cnt], dely[cnt]);
			}
		}
	}
	
	void recover() {
		for (int x = 1; x <= n; ++x) {
			for (const int y : g[x]) {
				tree::modify(x, y);
			}
		}
	}
}

void read() {
	n = readInt(), m = readInt();
	for (int i = 1; i <= m; ++i) {
		origin::add(readInt(), readInt());
	}
	
	q = op;
	while ((q->op = readInt()) != -1) {
		q->u = readInt(), q->v = readInt();
		if (q->op == 0) origin::del(q->u, q->v);
		++q;
	}
}

void solve() {
	static int ans[N], cnt = 0;
	while (q-- != op) {
		// printf("Solving op %d, %d, %d\n", q->op, q->u, q->v);
		if (q->op) {
			ans[cnt++] = tree::query(q->u, q->v);
		} else {
			tree::modify(q->u, q->v);
		}
	}
	while (cnt--) {
		printf("%d\n", ans[cnt]);
	}
}

int main() {
	read();
	origin::toTree();
	tree::preWork();
	// printf("Pre work ok\n");
	origin::recover();
	// printf("Recover ok\n");
	solve();
	return 0;
}