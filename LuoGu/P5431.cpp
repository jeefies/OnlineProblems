#include <iostream>

typedef long long ll;

ll quickPow(ll a, ll x, ll p) {
	ll r = 1;
	while (x) {
		if (x & 1) r = (r * a) % p;
		x >>= 1, a = (a * a) % p;
	}
	return r;
}

int main() {
	int n, p, base, k = 1;
	scanf("%d %d %d", &n, &p, &base);
	int a;
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		k = (k * base) % p;
		scanf("%d", &a);
		ll inv = quickPow(a, p - 2, p);
		ans = (ans + inv * k) % p;
	}
	
	printf("%lld\n", ans);
}