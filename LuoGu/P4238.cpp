#include <complex>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int mod = 998244353, g = 3, ig = 332748118;
typedef long long lint;

inline lint qpow(lint a, int x) {
	lint r = 1;
	for (; x; x >>= 1, a = a * a % mod)
		if (x & 1) r = r * a % mod;
	return r;
}

typedef vector<lint> vec;
vector<int> rev;
void NTT(vec &v, int O, int inv) {
	clog << "In NTT, transforming: ";
	for (int i = 0; i < O; ++i) {
		if (i < rev[i]) swap(v[i], v[rev[i]]);
		clog << v[i] << ' ';
	} clog << '\n';
	
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
		clog << "INV...\n";
		lint iv = qpow(O, mod - 2);
		for (int i = 0; i < O; ++i)
			v[i] = v[i] * iv % mod;
	}
	clog << "NTT Done: ";
	for (int i = 0; i < O; ++i) {
		clog << v[i] << ' ';
	} clog << '\n';
}

void initRev(int n) {
	int lp = 0;
	for (int i = 2; i < n; i <<= 1) ++lp;
	for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << lp);
}

// A, B are all n/2
void polyMul(vec &A, vec &B, int n) {
	static vec tA(0), tB(0);
	
	tA.resize(n), tB.resize(n);
	for (int i = (n >> 1) - 1; ~i; --i) tA[i] = A[i], tB[i] = B[i];
	for (int i = (n >> 1); i < n; ++i) tA[i] = tB[i] = 0;
	
	initRev(n);
	NTT(tA, n, 1), NTT(tB, n, 1);
	for (int i = 0; i < n; ++i) tA[i] = tA[i] * tB[i] % mod;
	NTT(tA, n, -1);
	A.assign(tA.begin(), tA.begin() + n);
}

void polyInv(vec &A, vec &B, int n) {
	int O = 1, logO = 0;
	while (O < n * 2) O <<= 1, ++logO;
	clog << "O: " << O << '\n';
	
	B.assign(O, 0), rev.assign(O, 0);
	vec C(O), tmp(O);
	
	// init
	B[0] = qpow(A[0], mod - 2); // mod x^1
	for (int p = 2, lp = 2; p < n * 2; p <<= 1, ++lp) {
		// init C
		for (int i = 0; i < p; ++i)
			C[i] = 2 * B[i] % mod;
			
		// init B'^2
		clog << "Mul B\n";
		polyMul(B, B, p);
		
		clog << "B'^2 to:\n";
		for (int i = 0; i < p; ++i) {
			clog << B[i] << ' ';
		} clog << '\n';
		
		
		// init A -> tmp
		for (int i = 0; i < p; ++i) tmp[i] = A[i];
		// calc -AB'^2
		polyMul(tmp, B, (p << 1));
		
		/*
		clog << "AB'^2 to: \n";
		for (int i = 0; i < (p << 1) ; ++i) {
			clog << tmp[i] << ' ';
		} clog << '\n';
		*/
		
		for (int i = 0; i < p; ++i)
			C[i] += mod - tmp[i], C[i] %= mod;
			
		swap(B, C);
		/*
		clog << "Cur Inv:\n";
		for (int i = 0; i < p; ++i) {
			clog << B[i] << ' ';
		} clog << '\n';
		*/
	}
	
	for (int i = 0; i < n; ++i) {
		cout << B[i] << ' ';
	}
}

int main() {
//	cin.tie(0)->sync_with_stdio(false);
	
	int n;
	cin >> n;
	
	vec A(n), B;
	for (int i = 0; i < n; ++i) cin >> A[i];
	polyInv(A, B, n);
}
