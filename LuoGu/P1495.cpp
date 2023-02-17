#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll m[11], a[11], Mm[11], y[11];

void extgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1, y = 0;
		return; 
	}
	extgcd(b, a % b, y, x);
	y -= (a / b) * x;
}

int main() {
	int n; scanf("%d", &n);
	
	ll M = 1;
	
	for (int i = 0; i < n; i++) {
		scanf("%lld%lld", m + i, a + i);
		M *= m[i];
	}
	
	for (int i = 0; i < n; i++) {
		Mm[i] = M / m[i];
	}
	
	for (int i = 0; i < n; i++) {
		ll x, tmp, mi = m[i];
		extgcd(Mm[i], mi, x, tmp);
		y[i] = (x + mi) % mi;
	} 
	
	ll x = 0;
	for (int i = 0; i < n; i++) {
		x = (x + a[i] * Mm[i] * y[i]) % M;
	}
	
	printf("%lld\n", x);
	return 0;
}
