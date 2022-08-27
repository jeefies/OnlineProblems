#include <stdio.h>
#include <stdlib.h>

int calc(int n) {
	int x = n;

	// search first 01
	int one = 0, bits = 0;
	while (bits < 32) {
		if (x & 1) {
			one++;
		} else if (one != 0) { // x & 1 == 0
			break;
		}
		bits++;
		x = x >> 1;
	}

	x += 1;
	x = x << bits - one + 1;
	for (int i = 0; i < one - 1; i++) {
		x = (x << 1) + 1;
	}

	return x;
}

int main() {
	int n;
	while (scanf("%d", &n) && n != 0) {
		printf("%d\n", calc(n));
	}
	return 0;
}
