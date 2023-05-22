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

lint fac[N] = {1}, ifac[N], invx[N];
void prepare(int n) {
	for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; --i) ifac[i - 1] = ifac[i] * i % mod;
}


vector<int> rev(N);
inline void initRev(int n) {
	int lp = 0;
	for (int i = 2; i < n; i <<= 1) ++lp;
	for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << lp);
}

inline void NTT(poly &v, int O, int inv) {
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

poly sf(N), sg(N), sw(N);
void solve(poly &ret, int n) {
	if (n == 1) {
		ret[1] = 1; return;
	}

	if (n & 1) {
		solve(ret, n - 1);
		for (int i = n; i; --i) ret[i] = (ret[i] * (n - 1) + ret[i - 1]) % mod;
		ret[0] = ret[0] * (n - 1) % mod;
		return;
	}

	// now, n == n / 2 * 2...
	int k = n >> 1;
	solve(ret, k);
	lint ki = 1;
	for (int i = 0; i <= k; ++i, ki = ki * k % mod) {
		sg[i] = ki * ifac[i] % mod;
		sf[i] = ret[i] * fac[i] % mod;
		// sf[i] = ret[k - i] * fac[k - i] % mod;
	} reverse(sf.begin(), sf.begin() + k + 1);
	// log("f: ", sf, k + 1), log("g: ", sg, k + 1);

	int O = 1; while (O < (k + 1) * 2) O <<= 1;
	initRev(O);
	NTT(sg, O, 1), NTT(sf, O, 1);
	for (int i = 0; i < O; ++i) sg[i] = sg[i] * sf[i] % mod;
	NTT(sg, O, -1);

	for (int i = 0; i <= k; ++i) sw[i] = sg[k - i] * ifac[i] % mod;

	NTT(sw, O, 1), NTT(ret, O, 1);
	for (int i = 0; i < O; ++i) ret[i] = ret[i] * sw[i] % mod;
	NTT(ret, O, -1);
	fill(ret.begin() + n + 1, ret.begin() + O, 0);
	fill_n(sw.begin(), O, 0);
	fill_n(sf.begin(), O, 0);
	fill_n(sg.begin(), O, 0);
	// log("now ret: ", ret, n + 1);
}

poly ret(N);
int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n;
	cin >> n;
	prepare(n << 1);
	solve(ret, n);
	for (int i = 0; i <= n; ++i) cout << ret[i] << ' ';
	cout << '\n';
	// log("", ret, n + 1);
}
