#include <cstdio>

long long add(long long a, long long b, long long p) {
	long long r = 0;
	while (b) {
		if (b & 1) r = (r + a) % p;
		a = (a + a) % p, b >>= 1;
	}
	return r;
}

int main() {
	long long a, b, p;
	scanf("%lld%lld%lld", &a, &b, &p);
	printf("%lld", add(a, b, p));
	return 0;
}