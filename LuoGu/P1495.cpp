#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll m[11], a[11], Mm[11], y[11];

// base ^ n
ll quickpow(int base, int n, int p) {
	int ans = 1;
	while (n) {
		base %= p;
		if (n & 1) ans = (ans * base) % p;
		n >>= 1;
		base = base * base;
	}
	return ans > 0 ? ans : p;
}

void extgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1, y = 0;
		return; 
	}
	extgcd(b, a % b, x, y);
	y = x - (a / b) * (x = y);
} 

int main() {
	int n; scanf("%d", &n);
	
	ll M = 1;
	
	for (int i = 0; i < n; i++) {
		scanf("%lld%lld", m + i, a + i);
		M *= m[i];
	}
	// printf("scan ok, get M %lld\n", M);
	for (int i = 0; i < n; i++) {
		Mm[i] = M / m[i];
		// printf("Mm[%d] = %lld\n", i, Mm[i]);
	}
	// printf("calc Mm ok\n");
	
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum = (sum + Mm[i] % M * a[i]) % M;
	}
	
	// printf("%lld\n", sum);
	
	/*
	// 求模的逆
	// 求Mm[i] 模 m[i]的逆 
	// x * Mm[i] = 1 (mod m[i])
	// 由费马小定理得
	// Mn[i] ^ (m[i] - 1) = 1 (mod m[i])
	// 所以 
	// Mn[i] ^ (m[i] - 2) * Mn[i] = 1 (mod m[i])
	// 即Mn[i] ^ (m[i] - 2) 为 Mn[i]模m[i]的逆元 
	// 但前提是 Mm[i]与m[i]互质，所以，这道题不能这么求 
	for (int i = 0; i < n; i++) {
		y[i] = quickpow(Mm[i], m[i] - 2, m[i]);
		printf("%lld, inv for %lld\n", y[i], Mm[i]);
	}
	*/
	
	// 扩展欧几里得算法
	for (int i = 0; i < n; i++) {
		ll x, tmp, mi = m[i];
		extgcd(Mm[i], mi, x, tmp);
		y[i] = (x + mi) % mi;
	} 
	// printf("calc 逆元 ok\n");
	
	ll x = 0;
	for (int i = 0; i < n; i++) {
		x = (x + a[i] * Mm[i] * y[i]) % M;
	}
	
	printf("%lld\n", x);
}
