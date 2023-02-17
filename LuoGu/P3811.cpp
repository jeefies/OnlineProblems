#include <iostream>

const int N = 3e6 + 7;

long long inv[N] = {0, 1};

int main() {
	int n, p;
	scanf("%d %d", &n, &p);
	
	for (int i = 2; i <= n; ++i) {
		inv[i] = inv[p % i] * (p - p / i) % p;
	}
	
	for (int i = 1; i <= n; ++i) {
		printf("%lld\n", inv[i]);
	}
}