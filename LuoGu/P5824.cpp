#include <iostream>
#include <algorithm>

using namespace std;
const int N = 4e5 + 10, mod = 998244353, g = 3, ig = 332748118;
typedef long long lint;

inline lint qpow(lint a, int x) {
	lint r = 1;
	for (; x; x >>= 1, (a *= a) %= mod) 
		if (x & 1) (r *= a) %= mod;
	return r; 
}

int n, m; // nÇò£¬mºÐ×Ó 
lint fac[N + 1] = {1}, ifac[N + 1], inv[N + 1];
inline void prepare() {
	for (int i = 1; i <= N; ++i) fac[i] = fac[i - 1] * i % mod;
	ifac[N] = qpow(fac[N], mod - 2);
	for (int i = N; i; --i) ifac[i - 1] = ifac[i] * i % mod;
}

inline lint C(int n, int m) {
	if (n < m) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

inline void calc1() {
	cout << qpow(m, n) << '\n';
}

inline void calc2() {
	if (n > m) {
		cout << "0" << '\n';
		return;
	}
	cout << fac[m] * ifac[m - n] << '\n';
}

inline void calc3() {
	if (n < m) {
		cout << "0" << '\n';
		return;
	}
	
	int neg = 1;
	lint ans = 0;
	for (int i = 0; i <= m; ++i, neg = -neg) {
		ans += neg * C(m, i) * qpow(i, n) % mod;
		ans %= mod;
	}
	cout << (ans + mod) % mod << '\n';
}

typedef vector<lint> Vector;
void NTT(Vector &v, int O, int inv) {
	vector<int> rev(O);
	int logO = floor(log((long double)O) / log(2.0f));
	cout << "In NTT, logO: " << logO << endl;
	for (int i = 0; i < O; ++i) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << logO);
		if (i < rev[i]) swap(v[i], v[rev[i]]);
	}
	
	for (int k = 2; k <= O; k <<= 1) {
		lint omega = qpow((~inv ? g : ig), (mod - 1) / k);
		for (int i = 0; i < O; i += k) {
			lint w = 1;
			for (int j(0), je = (k >> 1); j < je; ++j, (w *= omega) %= mod) {
				lint s = v[i + j], t = v[i + j + k] * w % mod;
				v[i + j] = (s + t) % mod, v[i + j + k] = (s - t + mod) % mod;
			}
		}
	}
	
	if (inv == -1) {
		cout << "IV NTT..." << endl;
		int iv = qpow(O, mod - 2);
		for (int i = 0; i < O; ++i)
			v[i] = v[i] * iv % mod;
	}
	
	printf("NTT Done!\n");
}

Vector A, B, S;
inline void calc4() {
	// sum i in [1, m] S(n, i)
	cout << "???"  << '\n';
	int O = 1;
	while (O <= m * 2) O <<= 1;
	A.resize(O), B.resize(O), S.resize(O);
	cout << "O: " << O << '\n';
	// A(x) = sum i in [0, m] i^n/i! * x^i
	// B(x) = sum i in [0, m] (-1)^(m-i) / (m-i)! * x^i
	for (int i = 0; i <= m; ++i) {
		A[i] = qpow(i, n) * ifac[i] % mod;
		B[i] = ((m - i) & 1 ? mod - 1 : 1) * ifac[m - i];
	}
	printf("NTT A\n");
	NTT(A, O, 1);
	printf("??????\n");
	printf("NTT B\n");
	NTT(B, O, 1);
	
	for (int i = 0; i <= m; ++i) {
		S[i] = A[i] * B[i] % mod; 
	} NTT(S, O, -1);
	
	lint sum = 0;
	for (int i = 0; i <= m; ++i) {
		sum = (sum + S[i]) % mod;
	} cout << sum << '\n';
}

inline void calc5() {
	cout << ((n > m) ? "0" : "1") << '\n';
}

inline void calc6() {
	// S(n, m)
	int neg = 1;
	lint ans = 0;
	for (int i = 0; i <= m; ++i, neg = -neg) {
		ans += neg * C(m, i) * qpow(m - i, n);
	} ans = ans * ifac[m] % mod;
	cout << (ans + mod) % mod << '\n';
}

inline void calc7() {
	cout << C(n + m - 1, m - 1) << '\n';
}

inline void calc8() {
	cout << C(m, n) << '\n';
}

inline void calc9() {
	cout << C(n - 1, m - 1) << '\n';
}

inline void calc10() {
	
}

int main() {
//	cin.tie(0)->sync_with_stdio(false);
	
//	cin >> n >> m;
	n = 13, m = 6;
	cout << "n: " << n << "m: " << m << '\n';
	
	prepare();
	calc1();
	calc2();
	calc3();
	calc4();
	calc5();
	calc6();
	calc7();
	calc8();
}
