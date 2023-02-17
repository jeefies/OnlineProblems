#include <iostream>
#include <cstdlib>

using std::max;

#define ll long long

const int N = 2e5 + 7, INF = 0x3F3F3F3F;
int m, d;

ll st[N * 4];

// build, all is zero, there's no sense to do that!

void change(int p, int tl, int tr, int i, ll v) {
	if (tl == tr /* && tl == i */) {
		st[p] = v;
		return;
	}
	
	int mid = (tl + tr) / 2;
	if (i <= mid)
		change(p * 2, tl, mid, i, v);
	else
		change(p*2 + 1, mid + 1, tr, i, v);
	
	st[p] = max(st[p * 2], st[p*2 + 1]);
	return;
}

ll query(int p, int tl, int tr, int l, int r) {
	if (l <= tl && tr <= r) {
		// total include
		return st[p];
	}
	
	int mid = (tl + tr) / 2;
	ll ans = -INF;
	if (l <= mid) 
		ans = query(p * 2, tl, mid, l, r);
	if (mid < r) 
		ans = max(ans, query(p*2 + 1, mid + 1, tr, l, r));
	return ans;
}


int main() {
	scanf("%d %d", &m, &d);
	int r = 0; // empty tree.
	ll n, t = 0; // last num
	char tmp;
	for (int i = 1; i <= m; ++i) {
		do tmp = getchar(); while (tmp != 'A' && tmp != 'Q');
		scanf("%lld", &n);
		
		if (tmp == 'Q') {
			t = query(1, 1, m, r - n + 1, m);
			printf("%lld\n", t);
		} else {
			change(1, 1, m, ++r, (n + t) % d);
		}
	}
	
	return 0;
}