#include <iostream>

typedef int ll;
const int N = 1e5 + 7;

struct SegmentTree {
	int l, r;
	ll sum;
	ll add, mul;
} t[N * 4];

ll a[N];
int mod;

#define update(p) (t[p].sum = (t[p * 2].sum + t[p*2 + 1].sum) % mod)

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	t[p].mul = 1;
	
	if (l == r) {
		t[p].sum = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p * 2, l, mid); // [l, mid]
	build(p * 2 + 1, mid + 1, r); // [mid + 1, r]
	update(p);
}

void sync(int p) {
	if (t[p].add) {
		t[p * 2].sum += t[p].add * (t[p * 2].r - t[p * 2].l + 1);
		t[p * 2].sum %= mod;
		t[p * 2].add += t[p].add;

		t[p*2 + 1].sum += t[p].add * (t[p*2 + 1].r - t[p*2 + 1].l + 1);
		t[p*2 + 1].sum %= mod;
		t[p*2 + 1].add += t[p].add;
		t[p].add = 0;
	}
	
	if (t[p].mul != 1) {
		t[p * 2].sum = (t[p * 2].sum * t[p].mul) % mod;
		t[p * 2].mul *= t[p].mul;
		
		t[p*2 + 1].sum = (t[p*2 + 1].sum * t[p].mul) % mod;
		t[p*2 + 1].mul *= t[p].mul;
		t[p].mul = 1;
	}
}

#define ADD 0
#define MUL 1

void change(int p, int l, int r, ll k, int op) {
	if (l <= t[p].l && t[p].r <= r) {
		if (op == ADD) {
			t[p].sum += k * (t[p].r - t[p].l + 1);
			t[p].sum %= k;
			t[p].add += k;
		} else {
			t[p].sum = t[p].sum * k % mod;
			t[p].mul *= k;
		}
		return;
	}

	sync(p);

	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) change(p * 2, l, r, k, op);
	if (r > mid) change(p * 2 + 1, l, r, k, op);

	update(p);
}

ll query(int p, int l, int r) {
	if (l <= t[p].l && t[p].r <= r) {
		return t[p].sum;
	}

	sync(p);

	int mid = (t[p].l + t[p].r) >> 1;
	ll val = 0;
	if (l <= mid) val += query(p * 2, l, r);
	if (r > mid) val += query(p * 2 + 1, l, r);
	return val % mod;
}

int main() {
	int n, m;
	scanf("%d %d %d", &n, &m, &mod);

	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	build(1, 1, n);

	ll op, x, y, k;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d %d %d", &x, &y, &k);
			change(1, x, y, k, MUL);	
		} else if (op == 2) {
			scanf("%d %d %d", &x, &y, &k);
			change(1, x, y, k, ADD);
		} else if (op == 3){
			scanf("%d %d", &x, &y);
			printf("%d\n", query(1, x, y));
		}
	}
	return 0;
}
