#include <stdio.h>

long long quickPow(long long a, long long b, long long p) {
	long long r = 1;
	while (b) {
		if (b & 1) r = (r * a) % p;
		a = (a * a) % p, b >>= 1;
	}
	return r % p;
}

int main() {
	int a, b, p;
	scanf("%d %d %d", &a, &b, &p);
	printf("%lld", quickPow(a, b, p));
	return 0;
}