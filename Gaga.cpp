#include <iostream>

const int N = 1e5 + 7;

struct SegTree {
	int ltp, rtp;
	int sum, ma;
} tree[N];
int ttot = 0;

int n;
int root[N];

int newTree() {
	return ++ttot;
}

#define MAX 0
#define SUM 1
#define lp tree[p].ltp
#define rp tree[p].rtp

int queryM(int p, int l, int r, int tl, int tr) {
	if (tl <= l && r <= tr) return tree[p].ma;
	
	int ans = 0;
	int mid = (l + r) >> 1;
	if (lp && tl <= mid) ans = queryM(lp, l, mid, tl, tr);
	if (rp && mid < tr) ans = max(ans, queryM(rp, mid + 1, r, tl, tr));
	return ans;
}

int queryS(int p, int l, int r, int tl, int tr) {
	if (tl <= l && r <= tr) return tree[p].sum;
	
	int ans = 0;
	int mid = (l + r) >> 1;
	if (lp && tl <= mid) ans = queryS(lp, l, mid, tl, tr);
	if (rp && mid < tr) ans += queryS(rp, mid + 1, r, tl, tr);
	return ans;
}

int query(int id, int l, int r, int op) {
	if (!root[id]) root[id] = newTree();
	return op == SUM ? queryS(root[id], 1, n, l, r) : queryM(root[id], 1, n, l, r);	
}