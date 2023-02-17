#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>

#define int long long

using std::vector;
using std::cout;
const int N = 1e6 + 7;

template<typename T>
inline T gcd(T x, T y) {
	T z;
	while (y) z = x % y, x = y, y = z;
	return x;
}

template<typename T>
inline T qpow(T a, T x, T p) {
	T r(1); a %= p;
	while (x) {
		if (x & 1) r = (r * a) % p;
		a = (a * a) % p, x >>= 1;
	}
	return r;
}

int phi[N], notp[N];
std::vector<int> prm;
void getPrm() {
	phi[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!notp[i]) prm.push_back(i), phi[i] = i - 1;
		
		for (const int &j : prm) {
			if (i * j >= N) break;
			notp[i * j] = true;
			if (i % j == 0) {
				// i | n && i^2 | n => phi(n) = phi(n / i) * i
				phi[i * j] = phi[i] * j; break;
			} else {
				// i | n && not i^2 | n => phi(n) = phi(n / i) * (i - 1)
				phi[i * j] = phi[i] * phi[j];
			}
		}
	}
}

bool exists[N]; /*0 1 2 3 4*/ ;
void getExists() {
	exists[2] = exists[4] = true;
	for (int i = 1; i < (int)prm.size(); ++i) {
		int p = prm[i];
		for (long long q = p; q < N; q *= p) {
			exists[q] = true;
			if (q * 2 < N) exists[q * 2] = true;
		}
	}
	// printf("Exists init!\n");
}

// not only prime factors
void factorize(int x, vector<int> & v) {
	v.push_back(1);
	for (const int &p : prm) {
		if (p >= x) break;
		if (x % p == 0) v.push_back(x / p);
	}
}

void getAll(int p, vector<int> & v) {
	// no roots
	if (!exists[p]) return;
	
	int ph = phi[p];
	int fst, cur;
	vector<int> factors; factors.clear();
	factorize(ph, factors);
	
	// enum i which gcd(i, m) == 1
	// find first element i suit i^ph = 1 mod p
	for (int i = 1; ; ++i) {
		if (gcd(i, p) != 1) continue;
		// if (qpow(i, ph, p) != 1) continue;
		
		bool valid = true;
		// we need i only if i^ph = 1 mod p, not other numbers.
		for (auto &e : factors) {
			if (e != ph && qpow(i, e, p) == 1) {
				valid = false; break;
			}
		}
		
		if (valid) {
			fst = cur = i; break;
		}
	}
	
	for (int i(1); i <= ph; ++i) {
		if (gcd(i, ph) == 1) v.push_back(cur);
		cur = cur * fst % p;
	}
}

/*
6
2 1
4 1
25 2
36 1
9 6
18 1
*/

signed main() {
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	
	getPrm();
	getExists();
	
	int n, d, t;
	
	std::cin >> t;
	while (t--) {
		std::cin >> n >> d;
		
		static vector<int> v; v.clear();
		getAll(n, v);
		std::sort(v.begin(), v.end());
		
		cout << v.size() << '\n';
		for (size_t i = d - 1; i < v.size(); i += d) {
			cout << v[i] << ' ';
		}
		cout << std::endl;
	}
	return 0;
}