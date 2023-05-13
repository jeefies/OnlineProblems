#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 133335, BLOCK = 2048;

int lab[N], col[N];
struct Ques {
	int l, r, t, i;
	bool operator < (const Ques &q) {
		return (lab[l] ^ lab[q.l]) ? (l < q.l) : (lab[r] ^ lab[q.r] ? r < q.r : t < q.t);
	}
} qs[N];

struct Modi {
	int x, c;
} ms[N];

int n, m;

int tot = 0;
int but[1000001];
inline void add(int c) {
	tot += !but[c]++;
}

inline void del(int c) {
	tot -= !--but[c];
}

inline void fix(int l, int r, int t) {
	int x = ms[t].x, &c = ms[t].c;
	if (l <= x && x <= r) {
		add(c), del(col[x]);
	} swap(c, col[x]);
}

int res[N];
int main() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; ++i) {
		cin >> col[i];
		lab[i] = i / BLOCK;
	}
	
	char s[5];
	int mc = 0, qc = 0;
	for (int x, y, i = 0; i < m; ++i) {
		cin >> s >> x >> y;
		if (s[0] == 'Q') {
			++qc, qs[qc] = {x, y, mc, qc};
		} else {
			++mc, ms[mc] = {x, y};
		}
	} sort(qs + 1, qs + 1 + qc);
	
	int l = 1, r = 0, t = 0;
	for (int i = 1; i <= qc; ++i) {
		Ques &q = qs[i];
		while (r < q.r) add(col[++r]);
		while (r > q.r) del(col[r--]);
		while (l < q.l) del(col[l++]);
		while (l > q.l) add(col[--l]);
		while (t < q.t) fix(l, r, ++t);
		while (t > q.t) fix(l, r, t--);
		
		res[q.i] = tot;
	}
	
	for (int i = 1; i <= qc; ++i) {
		cout << res[i] << '\n';
	}
}