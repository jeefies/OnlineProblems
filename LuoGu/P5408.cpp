#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;
const int N = 1e6, mod = 167772161, g = 3, ig = 55924054;
typedef long long lint;
typedef vector<lint> poly;

lint qpow(lint a, int x) {
	lint r = 1;
	for (; x; x >>= 1, a = a * a % mod)
		if (x & 1) r = r * a % mod;
	return r;
}

inline void initRev(int n, vector<int> &rev) {
	rev.resize(n);
	int lp = 0;
	for (int i = 2; i < n; i <<= 1) ++lp;
	for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << lp);
}

inline void NTT(poly &v, vector<int> &rev, int O, int inv) {
	for (int i = 0; i < O; ++i) {
		if (i < rev[i]) swap(v[i], v[rev[i]]);
	}

	for (int u = 2; u <= O; u <<= 1) {
		lint omega = qpow((~inv ? g : ig), (mod - 1) / u);
		for (int i = 0; i < O; i += u) {
			lint w = 1;
			for (int j = 0, je = (u >> 1); j < je; ++j, w = w * omega % mod) {
				lint s = v[i + j], t = w * v[i + je + j] % mod;
				v[i + j] = (s + t) % mod, v[i + je + j] = (s - t + mod) % mod;
			}
		}
	}

	if (inv == -1) {
		lint iv = qpow(O, mod - 2);
		for (int i = 0; i < O; ++i)
			v[i] = v[i] * iv % mod;
	}
}

void log(const char *s, const poly &p, int n) {
	cout << s << "[";
	for (int i = 0; i < n - 1; ++i) {
		cout << p[i] << ", ";
	} cout << p[n - 1] << "]\n";
}

void log(const char *s, const vector<int> &p, int n) {
	cout << s << "[";
	for (int i = 0; i < n - 1; ++i) {
		cout << p[i] << ", ";
	} cout << p[n - 1] << "]\n";
}

int n;
poly depsB[30];
vector<int> revs[30];
inline void work(poly &ret, int l, int r, int dep) {
	// cout << "work in [" << l << ", " << r << "], dep: " << dep << '\n';
	if (l + 1 == r) {
		ret.assign(ret.size(), 0);
		if (l < n) ret[0] = l, ret[1] = 1;
		else ret[0] = 1;
		return;
	}

	int mid = (l + r) >> 1, o = 2 << dep;
	poly &B = depsB[dep];
	vector<int> &rev = revs[dep];
	work(ret, l, mid, dep - 1), work(B, mid, r, dep - 1);

	// log("\trev: ", rev, o);
	// cout << "merge in [" << l << ", " << r << "]:\n";
	// log("\tA: ", ret, o), log("\tB: ", B, o);
	NTT(ret, rev, o, 1), NTT(B, rev, o, 1);
	for (int i = 0; i < o; ++i) ret[i] = B[i] * ret[i] % mod;
	NTT(ret, rev, o, -1);
	// log("\tret: ", ret, o);
}

poly ret(N);
int main() {
	cin.tie(0)->sync_with_stdio(false);

	cin >> n;

	int O = 1, dep = 0;
	while (O < n) {
		O <<= 1, ++dep;
		depsB[dep].resize(2 << dep), initRev(2 << dep, revs[dep]);
	}
	work(ret, 0, O, dep);
	for (int i = 0; i <= n; ++i) {
		cout << ret[i] << ' ';
	}
}
