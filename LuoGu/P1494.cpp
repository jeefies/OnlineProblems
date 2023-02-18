#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 5e4 + 7, BLOCK = 512;

struct Ques {
	int l, r, i;
} ques[N];

long long tot(0);
int label[N];
int n, q;
int color[N], but[N];
long long res[N][2];

template<typename T>
inline T gcd(T x, T y) {
	return y ? gcd(y, x % y) : x;
}

inline void add(int c) {
	tot += but[c];
	tot += ++but[c];
}

inline void del(int c) {
	tot -= but[c];
	tot -= --but[c];
}

int main() {
	cin.tie(0)->sync_with_stdio(false);

	cin >> n >> q;
	for (int i(1); i <= n; ++i) {
		cin >> color[i];
	}

	Ques * qptr = ques;
	for (int i(0); i ^ q; ++i, ++qptr) {
		cin >> qptr->l >> qptr->r;
		qptr->i = i;
	}

	sort(ques, qptr, [](const Ques &x, const Ques &y) {
		if ((x.l >> 9) ^ (y.l >> 9)) return x.l < y.l; // not same block
		return ((x.l >> 9) & 1) ? x.r < y.r : x.r > y.r;
	});

	qptr = ques;
	int l(1), r(0);
	for (int i(0); i ^ q; ++i, ++qptr) {
		while (r < qptr->r) add(color[++r]);
		while (r > qptr->r) del(color[r--]);
		while (l > qptr->l) add(color[--l]);
		while (l < qptr->l) del(color[l++]);

		int len = qptr->r - qptr-> l + 1;
		if (len == 1) {
			res[qptr->i][0] = 0, res[qptr->i][1] = 1;
			continue;
		}
		long long b = (long long)(len - 1) * len;
		int d(gcd(tot - len, b));
		res[qptr->i][0] = (tot - len) / d, res[qptr->i][1] = b / d;
	}

	for (int i(0); i ^ q; ++i) {
		cout << res[i][0] << '/' << res[i][1] << '\n';
	} cout << flush;
	return 0;
}
