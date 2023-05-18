#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
const int N = 1e6;
int BLOCK = 2048;

struct Ques {
	int l, r, i, t;
	bool operator < (const Ques &q) {
		if (l / BLOCK != q.l / BLOCK) return l < q.l;
		else if (r / BLOCK != q.r / BLOCK) return r < q.r;
		return t < q.t;
	}
} qs[N];

int ms[N][2];

int n, q;
int mc = 0, qc = 0;
int val[N], apps[N], apc = 0;

void input() {
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> val[i];
		apps[++apc] = val[i];
	}
	
	for (int op, x, y, i = 1; i <= q; ++i) {
		cin >> op >> x >> y;
		if (op == 1) {
			++qc, qs[qc] = {x, y, qc, mc};
		} else {
			++mc, ms[mc][0] = x, ms[mc][1] = y;
			apps[++apc] = y;
		}
	}
	
	BLOCK = pow(n, 2.0 / 3.0);
	sort(qs + 1, qs + 1 + qc);
	sort(apps + 1, apps + 1 + apc);
	int *appe = unique(apps + 1, apps + 1 + apc);
	for (int i = 1; i <= n; ++i) {
		val[i] = lower_bound(apps + 1, appe, val[i]) - apps;
	}
	for (int i = 1; i <= mc; ++i) {
		ms[i][1] = lower_bound(apps + 1, appe, ms[i][1]) - apps;
	}
}

int exi[N] = {0};
int but[N] = {N};
int res[N] = {0};

inline void add(int v) {
	--but[exi[v]], ++but[++exi[v]]; 
}

inline void del(int v) {
	--but[exi[v]], ++but[--exi[v]];
}

inline void fix(int l, int r, int t) {
	if (l <= ms[t][0] && ms[t][0] <= r) {
		add(ms[t][1]);
		del(val[ms[t][0]]);
	} swap(val[ms[t][0]], ms[t][1]);
}

void work() {
	int l = 1, r = 1, t = 0;
	but[0] = 1e9, add(val[1]);
	for (int i = 1; i <= qc; ++i) {
		Ques q = qs[i];
		while (l < q.l) del(val[l++]);
		while (l > q.l) add(val[--l]);
		while (r < q.r) add(val[++r]);
		while (r > q.r) add(val[r--]);
		while (t < q.t) fix(l, r, ++t);
		while (t > q.t) fix(l, r, t--);
		
		for (int j = 0; j <= 1000; ++j) {
			if (but[j] == 0) {
				res[q.i] = j; break;
			}
		}
	}
}

void output() {
	for (int i = 1; i <= qc; ++i) {
		cout << res[i] << '\n';
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(false);
	input();
	work();
	output();
}
