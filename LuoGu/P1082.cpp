#include <stdio.h>

#define int long long

int exgcd(int a, int b, int *s, int *t) {
	if (b == 0) {
		*s = 1, *t = 0;
		return a;
	}
	
	int ot, r = exgcd(b, a % b, s, t);
	ot = *t, *t = *s - (a / b) * *t, *s = ot;
	return r;
}

signed main() {
	int a, b, s, t;
	scanf("%lld %lld", &a, &b);
	int gcd = exgcd(a, b, &s, &t);
	b /= gcd;
	printf("%lld\n", (s % b + b) % b);
	return 0;
}