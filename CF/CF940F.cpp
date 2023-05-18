#include <iostream>
#include <algorithm>
#include <vector>

// Why Error at point 30?
// But OFFSET?????? FUCK YOU!
using namespace std;
const int N = 1e6 + 3, BLOCK = 2048;

int lab[N];
struct Ques {
	int l, r, i, t;
	bool operator < (const Ques &q) {
		if (lab[l] != lab[q.l]) return l < q.l;
		else if (lab[r] != lab[q.r]) return r < q.r;
		return t < q.t;
	}
} qs[N];

struct Modi {
	int x, v;
} ms[N];

int num[N];
int apps[N], tot = 0;

// but but
int exi[N];
int but[N] = {N};
inline void add(int v) {
	int &e = exi[v];
	--but[e + 100], ++but[++e + 100];
}

inline void del(int v) {
	int &e = exi[v];
	--but[e + 100], ++but[--e + 100];
}

inline void fix(int l, int r, int t) {
	int x = ms[t].x, &v = ms[t].v;
	if (l <= x && x <= r) {
		add(v), del(num[x]);
	} swap(v, num[x]);
//	clog << "Fixing time " << t << " in  " << l << "-" << r << '\n';
}

inline int QBut() {
	for (int k = 1 + 100; k <= 600; ++k)
		if (but[k] == 0) return k - 100;
	return -1; // NOT REACHED
}

int res[N];
int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= (n << 1); ++i) lab[i] = i / BLOCK;
	
	for (int i = 1; i <= n; ++i) {
		cin >> num[i];
		apps[++tot] = num[i];
	}
	
	
	int mc = 0, qc = 0;
	for (int op, x, y, i = 1; i <= q; ++i) {
		cin >> op >> x >> y;
		if (op == 1) {
			++qc, qs[qc] = {x, y, qc, mc};
		} else {
			++mc, ms[mc] = {x, y};
			apps[++tot] = y;
		}
	} sort(qs + 1, qs + 1 + qc);
	
	// discrete
	sort(apps + 1, apps + tot + 1);
	int * ae = unique(apps + 1, apps + tot + 1);
	for (int i = 1; i <= n; ++i)
		num[i] = lower_bound(apps + 1, ae, num[i]) - apps + 1;
	for (int i = 1; i <= mc; ++i)
		ms[i].v = lower_bound(apps + 1, ae, ms[i].v) - apps + 1;
	
	/*
	clog << "Discrete result:\nnums to: ";
	for (int i = 1; i <= n; ++i) 
		clog << num[i] << ' ';
	clog << "\nms to: ";
	for (int i = 1; i <= mc; ++i) {
		clog << "{" << ms[i].x << ", " << ms[i].v << "} ";
	} clog << '\n';
	*/
		
	int l = 0, r = 0, t = 0;
	for (int i = 1; i <= qc; ++i) {
		// clog << "At q " << i << '\n';
		Ques &q = qs[i];
		while (l > q.l) add(num[--l]);
		while (l < q.l) del(num[l++]);
		while (r < q.r) add(num[++r]);
		while (r > q.r) del(num[r--]);
		while (t < q.t) fix(l, r, ++t);
		while (t > q.t) fix(l, r, t--);	
		
		res[q.i] = QBut();
	}
	
	for (int i = 1; i <= qc; ++i) {
		cout << res[i] << '\n';
	}
	return 0;
}
