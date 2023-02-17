#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
inline void read(int mod, T & x) {
	x = 0; register char t, f(0), g(0);
	do { if ((t = getchar()) == '-') f = 1; } while (t < '0' || '9' < t);
	do {
		x = x * 10 + (t ^ 48), t = getchar();
		if (x >= mod) g = 1, x %= mod;
	} while ('0' <= t && t <= '9');
	if (f) x = -x;
	if (g) x += mod;
}

template <typename T, typename ...Args> inline void read(int mod, T &t, Args&... args) {
	read(mod, t), read(mod, args...);
}

int getphi(int x) {
	int phi = x;
	for (int i = 2; i * i <= x; ++i) {
		if (x % i) continue;
		phi = phi / i * (i - 1);
		do x /= i; while (x % i == 0);
	}
	if (x > 1) phi = phi / x * (x - 1);
	return phi;
}

long long quickPow(long long a, long long x, int p) {
	long long r = 1;
	while (x) {
		if (x & 1) r = (r * a) % p;
		a = (a * a) % p, x >>= 1;
	}
	return r;
}

int main() {
	int a, m, INF(numeric_limits<int>::max());
	read(INF, a, m);
	int phi = getphi(m);
	long long b; read(phi, b);
	printf("%d %lld\n", phi, b);
	printf("%lld\n", quickPow(a, b, m));
}