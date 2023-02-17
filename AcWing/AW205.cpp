#include <iostream>
#include <algorithm>
#include <cstring>

const int MOD = 10000;

int I[2], fib[2][2];

inline void mul() {
	// a * fib
	static int c[2];
	c[0] = (I[0] * fib[0][0] + I[1] * fib[1][0]) % MOD;
	c[1] = (I[0] * fib[0][1] + I[1] * fib[1][1]) % MOD;
	I[0] = c[0], I[1] = c[1];
}

inline void mulBase() {
	static int c[2][2];
	
	c[0][0] = (fib[0][0] * fib[0][0] + fib[0][1] * fib[1][0]) % MOD;
	c[1][0] = (fib[1][0] * fib[0][0] + fib[1][1] * fib[1][0]) % MOD;
	c[0][1] = (fib[0][0] * fib[0][1] + fib[0][1] * fib[1][1]) % MOD;
	c[1][1] = (fib[1][0] * fib[0][1] + fib[1][1] * fib[1][1]) % MOD;
	memcpy(fib, c, sizeof(c));
}

int main() {
	int n;
	while (~scanf("%d", &n) && n != -1) {
		if (n <= 2) {
			printf("%d\n", n ? 1 : 0);
			continue;
		}
		
		I[0] = 1, I[1] = 0;
		fib[0][0] = fib[0][1] = fib[1][0] = 1;
		fib[1][1] = 0;
		
		while (n) {
			if (n & 1) mul();
			mulBase(), n >>= 1;
		}
		printf("%d\n", I[1]);
	}
}