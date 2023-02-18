#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 1e5, MOD = 999911659, PHI = 999911657;
const int P[] = {2, 3, 4679, 35617};

int fac[N] = {1}, ifac[N];

template<typename T, typename X, typename P>
T qpow(T a, X x, P p) {
	a %= p;
	T r(1);
	while (x) {
		if (x & 1) r = (long long)r * a % p;
		a = (long long)a * a % p, x >>= 1;
	}
	return r;
}

void init(int p) {
	for (int i = 1; i < p; ++i) fac[i] = (long long)fac[i - 1] * i % p;
	ifac[p - 1] = qpow(fac[p - 1], p - 2, p);
	for (int i = p - 1; i; --i) ifac[i - 1] = (long long)ifac[i] * i % p;
}

// i <= j
int C(int i, int j, int p) {
	if (i > j) return 0;
	return (long long)fac[j] * ifac[i] % p * ifac[j - i] % p;
}

int Lucas(int i, int j, int p) {
	if (i == 0) return 1;
	return (long long)Lucas(i / p, j / p, p) * C(i % p, j % p, p) % p;
}

void factorize(int x, vector<int> &v) {
	v.reserve(100);
	for (int i = 1; i * i <= x; ++i) {
		if (x % i == 0) {
			v.push_back(i);
			if (i * i != x) v.push_back(x / i);
		}
	}
}

namespace EXCRT {
	typedef long long jint;
	struct Equation {
		jint a, p;
	};

	template<typename T>
	T gcd(T a, T b) {
		return b ? gcd(b, a % b) : a;
	}
	
	template<typename T>
	T exgcd(T a, T b, T &x, T &y) {
		if (b == 0) {
			x = 1, y = 0;
			return a;
		}
	
		int t = exgcd(b, a % b, y, x);
		y -= (a / b) * x;
		return t;
	}

	Equation merge(const Equation &x, const Equation &y) {
		jint c = (y.a - x.a) % y.p;
		if (c < 0) c += y.p;
	
		// k1 x.p + k2 y.p = c
		jint d = gcd(x.p, y.p), k1, k2;
		exgcd(x.p / d, y.p / d, k1, k2);
	
		if (c % d) cout << "Failed\n"; // failed
	
		// find least positive k1
		k1 = k1 * (c / d) % y.p;
		if (k1 < 0) k1 += y.p;
	
		jint lcm = x.p / d * y.p;
		Equation r = {(x.a + k1 * x.p % lcm) % lcm, lcm};
		if (r.a < 0) r.a += lcm;
		return r;
	}
} 

int main() {
	int n, g;
	cin >> n >> g;

	if (g == MOD) return cout << "0\n", 0;

	vector<int> factors;
	factorize(n, factors);

	EXCRT::Equation r = {0, 1};
	for (auto p : P) {
		EXCRT::Equation e = {0, p};
		init(p);
		for (auto fact : factors) {
			e.a = (e.a + Lucas(fact, n, p)) % p;
		}
		r = EXCRT::merge(r, e);
	}
	cout << qpow(g, r.a, MOD) << endl;
	return 0;
}
