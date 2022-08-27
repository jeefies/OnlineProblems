#include <iostream>
#include <cstdio>

using namespace std;

long quickpow(long base, long b, long p) {
	long mul = 1;
	while (b) {
		if (b & 1) mul = (mul * base) % p;
		base = (base * base) % p, b >>= 1;
	}
	return mul % p;
}

int main() {
	long a, b, p;
	cin >> a >> b >> p;
	printf("%d^%d mod %d=%d\n", a, b, p, quickpow(a, b, p));
	return 0;
}
