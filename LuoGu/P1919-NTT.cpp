#include <complex>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
const int MOD = 998244353, g = 3, ig = 332748118;
const double PI = acos(-1);
int O(1), logO(0);

typedef vector<long long> vec;
typedef vector<int> ivec;

template <typename T, typename X>
T qpow(T a, X x, const int p) {
    T r = 1;
    while (x) {
        // no need to use quickMul when p*p can be smaller than int64.max !!!
        if (x & 1) r = (r * a) % p;
        a = (a * a) % p, x >>= 1;
    }
    return r;
}

void NTT(ivec &rev, vec &v, int inv) {
	for (int i(0); i < O; ++i) {
		if (rev[i] < i) std::swap(v[i], v[rev[i]]);
	}
	
	// 第 log(k) 次合并，合并之后长度为 (k<<1) 
	for (int k(1); k < O; k <<= 1) {
		long long omega = qpow((long long)(~inv ? g : ig), (MOD - 1) / (k << 1), MOD);
		for (int i(0); i < O; i += (k << 1)) {
			long long w(1);
			for (int j(0); j < k; ++j, w = w * omega % MOD) {
				long long s = v[i + j], t = w * v[i + j + k];
				v[i + j] = (s + t) % MOD, v[i + j + k] = ((s - t) % MOD + MOD) % MOD;
			}
		}
	}
	
	if (inv == -1) {
		for (int iv(qpow((long long)O, MOD - 2, MOD)), i(0); i < O; ++i) {
			v[i] = v[i] * iv % MOD;
		}
	}
}

int main() {
	std::string cA, cB;
	std::cin >> cA >> cB;
	
	int n = cA.size(), m = cB.size();
	while (O < n + m) O <<= 1, ++logO;
	
	// std::cout << n << ' ' << m << ' ' << O << ' ' << logO << '\n';
	
	vec A(O), B(O);
	for (int i(0); i < n; ++i) A[n - i - 1] = cA[i] - '0'; 
	for (int i(0); i < m; ++i) B[m - i - 1] = cB[i] - '0';
	
	// for (int i(0); i < O; ++i) std::cout << A[i].real << ' ' << B[i].real << '\n'; 
	
	ivec rev(O);
	for (int i(0); i < O; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (logO - 1));
	
	NTT(rev, A, 1), NTT(rev, B, 1);
	
	for (int i(0); i < O; ++i) A[i] = A[i] * B[i];
	NTT(rev, A, -1);
	
	int nm(n + m);
	for (int i(0); i <= nm; ++i) {
		if (A[i] >= 10) A[i + 1] += A[i] / 10, A[i] %= 10, nm += (i == nm);
	}
	while (!A[nm] && nm) --nm;
	while (nm >= 0) std::cout << A[nm--];
	return 0;
}
