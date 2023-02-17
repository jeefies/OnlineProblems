#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

const int N = 1e5 + 7;

// Ha!
inline int min(int a, int b) {
	return a > b ? a : b;
}

int n, m;
int a[N];

typedef int data;
namespace seg {
	struct SegTree {
		int lte, rte, li, ri, len;
		data mi, lazy;
		void init(int l, int r) {
			li = l, ri = r, len = r - l + 1;
		}
	} tree[N * 4];
	
	#define ct tree[p]
	#define lp ct.lte
	#define rp ct.rte
	#define lt tree[lp]
	#define rt tree[rp]
	
	int usage = 0;
	inline int newNode(int l, int r) {
		tree[++usage].init(l, r);
		return usage;
	}
	
	inline void sync(int p) {
		if (ct.lazy) {
			rt.lazy = lt.lazy = rt.mi = lt.mi = ct.lazy;
			ct.lazy = 0;
		}
	}
	inline void update(int p) {
		ct.mi = min(lt.mi, rt.mi);
		// printf("Update [%d, %d] (p %d) mi %d\n", ct.li, ct.ri, p, ct.mi);
	}
	inline void build(int p) {
		if (ct.li == ct.ri) {
			// ct.mi = origin[ct.li];
			ct.mi = a[ct.li];
			// printf("Build end set %d mi %d\n", ct.li, ct.mi);
			return;
		}
		
		int mid = (ct.li + ct.ri) >> 1;
		lp = newNode(ct.li, mid), rp = newNode(mid + 1, ct.ri);
		build(lp), build(rp);
		update(p);
	}
	void build() {
		// for (int i = 1; i <= n; ++i)
			// origin[dfn[i]] = def[i];
		build(newNode(1, n));
	}
	
	inline void change(int p, int l, int r, data val) {
		if (l <= ct.li && ct.ri <= r) {
			ct.mi = val, ct.lazy = val;
			return;
		}
		sync(p);
		int mid = (ct.li + ct.ri) >> 1;
		if (l <= mid) change(lp, l, r, val);
		if (mid < r)  change(rp, l, r, val);
		update(p);
	}
	void change(int l, int r, data val) {
		// printf("In changing [%d, %d] to %d\n", l, r, val);
		change(1, l, r, val);
		// printf("Out...\n");
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
		data ans = 0;
		query(1, l, r, ans);
		// printf("Out with ans %d\n", ans);
		return ans;
	}
}

void read() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	seg::build();
}

void proc() {
	int l, r;
	while (m--) {
		scanf("%d %d", &l, &r);
		printf("%d\n", seg::query(l, r));
	}
}

int main() {
	read();
	proc();
	return 0;
}