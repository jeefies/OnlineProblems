#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
const int mod = 998244353, g = 3, ig = 332748118;
const int N = 5e5;
typedef long long lint;
typedef vector<lint> poly;

void log(const string &s, const poly &p, int n) {
	return;
	clog << s << '\n';
	for (int i = 0; i < n; ++i) clog << p[i] << ' ';
	clog << '\n';
}

inline lint qpow(lint a, int x) {
	lint r = 1;
	for (; x; x >>= 1, a = a * a % mod)
		if (x & 1) r = r * a % mod;
	return r;
}

lint fac[N] = {1}, ifac[N], invx[N];
void prepare(int n) {
	for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; --i) {
		ifac[i - 1] = ifac[i] * i % mod;
		invx[i] = ifac[i] * fac[i - 1] % mod;
	}
}

int rev[N];
void initRev(int n) {
	static int prev = -1;
	if (n == prev) return;
	prev = n;
	
	int lp = 0;
	for (int i = 2; i < n; i <<= 1) ++lp;
	for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << lp);
}

void NTT(poly &v, int O, int inv) {
	initRev(O);
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

// make sure n = 2^k
poly tmpA(N), tmpB(N);
void polyMul(poly &A, const poly &B, int n) {
	copy_n(A.begin(), (n >> 1), tmpA.begin());
	copy_n(B.begin(), (n >> 1), tmpB.begin());
	fill_n(tmpA.begin() + (n >> 1), (n >> 1), 0);
	fill_n(tmpB.begin() + (n >> 1), (n >> 1), 0);
	
	NTT(tmpA, n, 1), NTT(tmpB, n, 1);
	for (int i = 0; i < n; ++i) tmpA[i] = tmpA[i] * tmpB[i] % mod;
	NTT(tmpA, n, -1);
	copy_n(tmpA.begin(), n, A.begin());
}

poly C(N), tmp(N);
void polyInv(poly &A, poly &ret, int n) {
	int O = 1;
	while (O < n * 2) O <<= 1; 
	ret.assign(O, 0);
	
	ret[0] = qpow(A[0], mod - 2);
	for (int p = 2, lp = 2; p < n * 2; p <<= 1, ++lp) {
		for (int i = 0; i < p; ++i)
			C[i] = 2 * ret[i] % mod;
			
		polyMul(ret, ret, p);
		for (int i = 0; i < p; ++i) tmp[i] = A[i];
		polyMul(tmp, ret, (p << 1));
		
		for (int i = 0; i < p; ++i)
			ret[i] = (C[i] + mod - tmp[i]) % mod;
	}
}

void polyDer(poly &A, poly &ret, int n) {
	for (int i = 1; i < n; ++i)
		ret[i - 1] = A[i] * i % mod;
	ret[n - 1] = 0;
}

void polyInvDer(poly &A, poly &ret, int n) {
	for (int i = 1; i < n; ++i)
		ret[i] = A[i - 1] * invx[i] % mod;
	ret[0] = 0;
}

void polyLn(poly &A, poly &ret, int n) {
	int O = 1;
	while (O < n * 2) O <<= 1;
	clog << "O: " << O << '\n';
	
	poly der(O), inv(O);
	polyDer(A, der, n);
//	log("poly der to:", der, n);
	polyInv(A, inv, n);
//	log("poly inv to:", inv, n);
	polyMul(der, inv, O);
//	log("poly mul to:", der, n);
	polyInvDer(der, ret, n);
//	log("poly inv der to:", ret, n);
}

void polyExp(poly &A, poly &ret, int n) {
	int O = 1;
	while (O < n * 2) O <<= 1;
	clog << "exp O: " << O << '\n';
	
	ret[0] = 1;
	poly ln(O), tA(O);
	for (int p = 2, lp = 2; p < n * 2; p <<= 1, ++lp) {
		clog << "At p: " << p << '\n';
		polyLn(ret, ln, p);
		log("poly ln to: ", ln, p);
		for (int i = 0; i < p; ++i) tA[i] = A[i];
		NTT(ret, p << 1, 1), NTT(ln, p << 1, 1), NTT(tA, p << 1, 1);
		for (int i = 0; i < (p << 1); ++i)
			ret[i] = ret[i] * ((1 + mod - ln[i] + tA[i]) % mod) % mod;
		NTT(ret, p << 1, -1), fill_n(ret.begin() + p, p, 0);
		log("final exp is: ", ret, p);
	}
}

poly A(N), expA(N);
int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	int n;
	cin >> n;
	prepare(n << 2);
	
	for (int i = 0; i < n; ++i) cin >> A[i];
	polyExp(A, expA, n);
	for (int i = 0; i < n; ++i) cout << expA[i] << ' ';
}
