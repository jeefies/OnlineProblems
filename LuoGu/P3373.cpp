#include <cstdio>

struct SegTree {
	int l, r; // [l, r]
	int sum, lazyAdd, lazyMul;
};

const int N = 1e5 + 7;

int a[N], n, m, mod;
SegTree t[N * 4];

// make sure lazyAdd and lazyMul would not be used at same time!!!
void sync(int p) {
	if (t[p].lazyAdd) {
		t[p * 2].sum = (t[p * 2].sum + (t[p * 2].r - t[p * 2].l + 1) * t[p].lazyAdd % mod) % mod;
		t[p * 2].lazyAdd = t[p].lazyAdd;
		
		t[p*2 + 1].sum = (t[p*2 + 1].sum + (t[p*2 + 1].r - t[p*2 + 1].l + 1) * t[p].lazyAdd % mod) % mod;
		t[p*2 + 1].lazyAdd = t[p].lazyAdd;
		
		t[p].lazyAdd = 0;
	}
	
	if (t[p].lazyMul != 1) {
		t[p * 2].sum = t[p * 2].sum * t[p].lazyMul % mod;
		t[p*2 + 1].sum = t[p * 2].sum * t[p].lazyMul % mod;
		t[p * 2].lazyMul = t[p*2 + 1].lazyMul = t[p].lazyMul;
		
		t[p].lazyMul = 1;
	}
	
	// printf("Syncing [%d, %d], sum to %d\n", t[p].l, t[p].r, t[p].sum);
}

int query(int p, int l, int r) {
	int tl = t[p].l, tr = t[p].r;
	if (l <= tl && tr <= r) {
		return t[p].sum;
	}
	
	sync(p);
	
	int ans = 0;
	int mid = (tl + tr) >> 1;
	if (l <= mid) ans = query(p * 2, l, r);
	if (mid < r) ans += query(p*2 + 1, l, r);
	return ans % mod;
}

#define MUL 1
#define ADD 0

void change(int p, int l, int r, int k, int op) {
	int tl = t[p].l, tr = t[p].r;
	// printf("In changing [%d, %d] (p %d)\n", tl, tr, p);
	
	if (l <= tl && tr <= r) {
		// printf("(OP = %d) End marking [%d, %d](p %d), org sum %d, ", op, tl, tr, p, t[p].sum);
		if (op == ADD) {
			t[p].sum = (t[p].sum + k * (t[p].r - t[p].l + 1)) % mod;
			t[p].lazyAdd += k;
		} else {
			t[p].sum = t[p].sum * k % mod;
			t[p].lazyMul *= k;
		}
		
		// printf(", lazyAdd %d, lazyMul %d\n", t[p].lazyAdd, t[p].lazyMul);
		// printf("\tsum to %d\n", t[p].sum);
		return;
	}
	
	sync(p);
	
	int mid = (tl + tr) >> 1;
	if (l <= mid) change(p * 2, l, r, k, op);
	if (mid < r) change(p*2 + 1, l, r, k, op);
	
	t[p].sum = (t[p * 2].sum + t[p*2 + 1].sum) % mod;
	// printf("Changing [%d, %d] (p %d) to %d\n", tl, tr, p, t[p].sum);
}

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	t[p].lazyAdd = 0, t[p].lazyMul = 1;
	
	if (l == r) {
		t[p].sum = a[l];
		return;
	}
	
	int mid = (l + r) >> 1;
	build(p * 2, l, mid), build(p*2 + 1, mid + 1, r);
	t[p].sum = (t[p * 2].sum + t[p*2 + 1].sum) % mod;
	
	// printf("Building [%d, %d] (p %d) sum %d\n", l, r, p, t[p].sum);
}

int main() {
	scanf("%d%d%d", &n, &m, &mod);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	
	build(1, 1, n);
	
	int op, x, y, k;
	
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &op, &x, &y);
		if (op == 3) {
			printf("%d\n", query(1, x, y));
		} else {
			scanf("%d", &k);
			change(1, x, y, k, 2 - op);
		}
	}
	return 0;
}