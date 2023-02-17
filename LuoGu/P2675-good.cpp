#include <iostream>
#include <algorithm>

const int N = 1e6 + 7, MOD = 10007;

int quickPow(int a, int x) {
	int r = 1;
	while (x) {
		if (x & 1) r = (r * a) % MOD;
		a = (a * a) % MOD, x >>= 1;
	}
	return r;
}

static int fac[N] = {1}, ifac[N];
inline int C(int i, int j) {
	if (i > j) return 0;
	return fac[j] * ifac[i] % MOD * ifac[j - i] % MOD;
}

inline int Lucas(int i, int j) {
	if (i == 0) return 1;
	return Lucas(i / MOD, j / MOD) * C(i % MOD, j % MOD) % MOD;
}

int main() {
	int n;
	scanf("%d", &n);
	
	int maxn = (n + 1) >> 1;
	for (int i = 1; i < MOD; ++i) fac[i] = (i * fac[i - 1]) % MOD;
	ifac[MOD - 1] = quickPow(fac[MOD - 1], MOD - 2);
	for (int i = MOD - 1; i; --i) ifac[i - 1] = ifac[i] * i % MOD;
	
	int ans = 0;
	if (n % 2) ans = Lucas(maxn - 1, n - 1) * (n % MOD) % MOD, --maxn;
	for (int i = 0; i < maxn; ++i) {
		ans = (ans + Lucas(i, n - 1) * ((i * 4 + 3) % MOD) % MOD) % MOD;
	}
	
	printf("%d\n", ans);
	return 0;
}