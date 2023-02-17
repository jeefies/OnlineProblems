#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 2e6 + 7;

int n, p;
int fac[N], ifac[N];

int qpow(int a, int x) {
	int r(1);
	while (x) {
		if (x & 1) r = (1ll * r * a) % p;
		a = (1ll * a * a) % p, x >>= 1;
	}
	return r;
}

int C(int i, int j) { // i <= j
	return 1ll * fac[j] * ifac[i] % p * ifac[j - i] % p;
}

int Lucas(int i, int j) {
	return i == 0 ? 1 : 1ll * Lucas(i / p, j / p) * C(i % p, j % p) % p;
}

void prepare() {
	int end = min(n, p - 1);
	fac[0] = 1;
	for (int i = 1; i <= end; ++i) fac[i] = 1ll * fac[i - 1] * i % p;
	ifac[end] = qpow(fac[end], p - 2);
	for (int i = end; i; --i) ifac[i - 1] = 1ll * ifac[i] * i % p;
}

int main() {
	scanf("%d %d", &n, &p);
	prepare();
	// make tree
	static int siz[N];
	for (int i = 1; i <= n; ++i) siz[i] = 1;
	for (int i = n; i; --i) siz[i>>1] += siz[i];
	
	// init dp
	static int dp[N];
	for (int i = (n<<1) + 1; i ^ n; --i) dp[i] = 1;
	for (int i = n; i; --i) dp[i] = 1ll * Lucas(siz[(i<<1)], siz[i] - 1) * dp[(i<<1)] % p * dp[(i<<1) | 1] % p;
	printf("%d\n", dp[1]);
	return 0;
}