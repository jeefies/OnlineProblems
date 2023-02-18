#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
const int N = 2e6;

struct Q {
	int l, r, t, i;
} qs[N];

struct M {
	int x, c;
} ms[N];

int n, m, tot(0), qc(0), mc(0), BLOCK;
int col[N], res[N], but[N];

inline void add(int c) {
	// if (++but[c] == 1) ++tot;
	tot += !but[c]++;
}

inline void del(int c) {
	// if (--but[c] == 0) --tot;
	tot -= !--but[c];
}

inline void fix(int l, int r, int t) {
	int x = ms[t].x, &c = ms[t].c;
	if (l <= x && x <= r) {
		del(col[x]), add(c);
	}
	swap(col[x], c);
}

inline bool Qcmp(const Q &x, const Q &y) {
	if (x.l / BLOCK ^ y.l / BLOCK) return x.l < y.l;
	if (x.r / BLOCK ^ y.r / BLOCK) return x.r < y.r;
	return x.t < y.t;
}

int main() {
	// cin.tie(0)->sync_with_stdio(false);

	// cin >> n >> m;
	// for (int i(1); i <= n; ++i) cin >> col[i];
	scanf("%d %d", &n, &m);
	for (int i(1); i <= n; ++i) scanf("%d", col + i);
	BLOCK = pow(n, 0.666);

	char op[3];
	int l, r;
	for (int i(1); i <= m; ++i) {
		// cin >> op >> l >> r;
		scanf("%s %d %d", op, &l, &r);
		if (op[0] == 'Q') {
			++qc, qs[qc] = {l, r, mc, qc};
		} else {
			++mc, ms[mc] = {l, r};
		}
	} sort(qs + 1, qs + 1 + qc, Qcmp);

	int t(0); l = 1, r = 0;
	for (int i(1); i <= qc; ++i) {
		const Q &q = qs[i];
		while (r < q.r) add(col[++r]);
		while (r > q.r) del(col[r--]);
		while (l < q.l) del(col[l++]);
		while (l > q.l) add(col[--l]);
		while (t < q.t) fix(l, r, ++t);
		while (t > q.t) fix(l, r, t--);

		res[q.i] = tot;
	}

	for (int i(1); i <= qc; ++i) {
		// cout << res[i] << '\n';
		printf("%d\n", res[i]);
	}
 
	return 0;
}
