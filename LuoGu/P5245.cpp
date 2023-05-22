#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 2e6 + 3;
const int mod = 998244353, g = 3, ig = 332748118;

typedef long long lint;
typedef vector<lint> poly;

void log(const string &s, const poly &p, int n) {
	clog << s << '\n';
	for (int i = 0; i < n; ++i) clog << p[i] << ' ';
	clog << '\n';
}

lint qpow(lint a, int x, int _mod = mod) {
	lint r = 1;
	for (; x; x >>= 1, a = a * a % _mod) 
		if (x & 1) r = r * a % _mod;
	return r;
}

lint fac[N] = {1}, ifac[N], invx[N];
void prepare(int n) {
	for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; --i) {
		invx[i] = ifac[i] * fac[i - 1] % mod;
		ifac[i - 1] = ifac[i] * i % mod;
	}
}

int rev[N];
void initRev(int n) {
	int lg = 0;
	for (int i = 2; i < n; (i <<= 1)) ++lg;
	for (int i = 0; i < n; ++i) 
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << lg);
}

void NTT(poly &v, int n, int inv) {
	for (int i = 0; i < n; ++i) 
		if (i < rev[i]) swap(v[i], v[rev[i]]);

	for (int u = 2; u <= n; u <<= 1) {
		lint omega = qpow((~inv ? g : ig), (mod - 1) / u);
		for (int i = 0, k = u >> 1; i < n; i += u) {
			lint w = 1;
			for (int j = 0; j < k; ++j, w = w * omega % mod) {
				lint s = v[i + j], t = v[i + j + k] * w % mod;
				v[i + j] = (s + t) % mod, v[i + j + k] = (s + mod - t) % mod;
			}
		}
	}

	if (inv == -1) {
		lint iv = qpow(n, mod - 2);
		for (int i = 0; i < n; ++i) (v[i] *= iv) %= mod;
	}
}

poly inv_a(N), inv_b(N);
void polyInv(const poly &v, poly &ret, int n) {
	int O = 1;
	while (O < n * 2) O <<= 1;

	fill_n(inv_a.begin(), O, 0), fill_n(inv_b.begin(), O, 0);
	ret[0] = qpow(v[0], mod - 2);
	for (int p = 2; p < n * 2; p <<= 1) {
		for (int i = 0; i < p; ++i) inv_b[i] = ret[i] * 2 % mod;

		initRev(p);
		NTT(ret, p, 1);
		for (int i = 0; i < p; ++i) ret[i] = ret[i] * ret[i] % mod;
		NTT(ret, p, -1);

		initRev(p << 1);
		for (int i = 0; i < p; ++i) inv_a[i] = v[i];
		NTT(ret, p << 1, 1), NTT(inv_a, p << 1, 1);
		for (int i = 0, ie = p << 1; i < ie; ++i) 
			inv_a[i] = ret[i] * inv_a[i] % mod;
		NTT(inv_a, p << 1, -1);

		for (int i = 0; i < p; ++i) {
			ret[i] = (inv_b[i] + mod - inv_a[i]) % mod;
			ret[i + p] = 0;
		}
	}

	for (int i = n; i < O; ++i) ret[i] = 0;
}

void polyDer(const poly &v, poly &ret, int n) {
	for (int i = 1; i < n; ++i)
		ret[i - 1] = i * v[i] % mod;
	ret[n - 1] = 0;
}

void polyInvDer(const poly &v, poly &ret, int n) {
	for (int i = 1; i < n; ++i)
		ret[i] = v[i - 1] * invx[i] % mod;
	ret[0] = 0;
}

poly ln_inv(N), ln_der(N);
void polyLn(const poly &v, poly& ret, int n) {
	int O = 1;
	while (O < n * 2) O <<= 1;

	fill_n(ln_inv.begin(), O, 0), fill_n(ln_der.begin(), O, 0);
	polyDer(v, ln_der, n);
	polyInv(v, ln_inv, n);

	initRev(O);
	NTT(ln_inv, O, 1), NTT(ln_der, O, 1);
	for (int i = 0; i < O; ++i) ln_der[i] = ln_der[i] * ln_inv[i] % mod;
	NTT(ln_der, O, -1);

	polyInvDer(ln_der, ret, n);
}

poly exp_ln(N), exp_a(N);
void polyExp(const poly &v, poly &ret, int n) {
	int O = 1;
	while (O < n * 2) O <<= 1;

	ret[0] = 1;
	for (int p = 2; p < n * 2; p <<= 1) {
		polyLn(ret, exp_ln, p);
		for (int i = 0; i < p; ++i) exp_a[i] = v[i];

		initRev(p << 1);
		NTT(ret, p << 1, 1), NTT(exp_ln, p << 1, 1), NTT(exp_a, p << 1, 1);
		for (int i = 0; i < (p << 1); ++i)
			ret[i] = ret[i] * ((1 + mod - exp_ln[i] + exp_a[i]) % mod) % mod;
		NTT(ret, p << 1, -1);

		fill_n(ret.begin() + p, p, 0);
	} fill(ret.begin() + n, ret.begin() + O, 0);
}

poly qpow_ret(N), qpow_ret2(N);
void polyQPow(poly &v, poly &ret, int n, int k) {
	if (k == 0) return ret[0] = 1, (void)0;
	int fa, rn;
	for (fa = 0; fa < n; ++fa) if (v[fa]) break;
	lint vf = v[fa], inv = qpow(v[fa], mod - 2);

	if (1ll * fa * k >= n) {
		// fill_n(ret.begin(), n, 0);
		return;
	}

	rn = n - fa;
	for (int i = 0; i < rn; ++i)
		v[i] = v[i + fa] % mod;
	fill(v.begin() + rn, v.begin() + n, 0);

	polyLn(v, qpow_ret, rn);
	for (int i = 0; i < rn; ++i) qpow_ret[i] = qpow_ret[i] * k % mod;
	polyExp(qpow_ret, qpow_ret2, rn);

	// log("ret: ", qpow_ret2, rn);

	inv = qpow(vf, k), rn = fa * k; // qpow(vf, k);
	for (int i = rn; i < n; ++i) ret[i] = qpow_ret2[i - rn] * inv % mod;
	fill_n(ret.begin(), rn, 0);
}

inline lint read() {
	lint x = 0; char c;
	do c = getchar(); while (c < '0' || c > '9');
	do x = ((x * 10) + (c - '0')) % mod, c = getchar(); while ('0' <= c && c <= '9');
	return x;
}

poly A(N), ret(N);
int main() {
	// cin.tie(0)->sync_with_stdio(false);

	int n = read(), k = read();
	prepare(n << 2);
	for (int i = 0; i < n; ++i) A[i] = read();
	polyQPow(A, ret, n, k);
	for (int i = 0; i < n; ++i) cout << ret[i] << ' ';
}
