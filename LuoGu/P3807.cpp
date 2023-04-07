#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
inline void read(T &x) {
	register char f(0), t; x = 0;
	do { if ((t = getchar()) == '-') f = 1; } while (t < '0' || '9' < t);
	do { x = (x<<1) + (x<<3) + (t ^ 48), t = getchar(); } while ('0' <= t && t <= '9');
	if (f) x = -x;
}
template<typename T, typename ...Args> inline void read(T &t, Args&... args) { read(t), read(args...); }

const int N = 1e5 + 7;

int fac[N] = {1}, ifac[N];
inline int quickPow(int a, int x, int p) {
	int r = 1;
	while (x) {
		if (x & 1) r = (1ll * r * a) % p;
		a = (1ll * a * a) % p, x >>= 1;
	}
	return r;
}

inline int C(int i, int j, int p) {
	// printf("Calc C(%d, %d)\n", i, j);
	if (i > j) return 0;
	return fac[j] * 1ll * ifac[i] % p * ifac[j - i] % p;
}

inline int Lucas(int i, int j, int p) {
	// printf("Calc Lucas(%d, %d)\n", i, j);
	if (i == 0) return 1;
	return Lucas(i / p, j / p, p) * 1ll * C(i % p, j % p, p) % p;
}

inline void prc() {
	int n, m, p;
	read(n, m, p);
	
	// fac, ifac
	for (int i = 1; i < p; ++i) fac[i] = (i * 1ll * fac[i - 1]) % p;
	ifac[p - 1] = quickPow(fac[p - 1], p - 2, p);
	for (int i = p - 1; i; --i) ifac[i - 1] = i * 1ll * ifac[i] % p;
	
	printf("%d\n", Lucas(n, n + m, p));
}

int main() {
	int T;
	read(T);
	while (T--) prc();
	return 0;
}