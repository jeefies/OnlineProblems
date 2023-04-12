#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

const int N = 1e5 + 7;

int n;
int a[N];
long long mod;

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

int main(int argc, char *argv[]) {
	int n, m;
	mod = 1e18 + 7;
	scanf("%d %d", &n, &m);


	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	// printf("Building:\n");
	build(1, 1, n);
	// printf("Build ok\n");

	int op, x, y, k;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d %d %d", &x, &y, &k);
			modify(1, 1, n, x, y, k);
		} else {
			scanf("%d %d", &x, &y);
			printf("%lld\n", query(1, 1, n, x, y));
		}
	}
	return 0;
}