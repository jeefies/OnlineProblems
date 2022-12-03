#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

char tree[1 << 10];

int main(int argc, char * argv[]) {
	int n;
	scanf("%d", &n);
	int most = pow(2, n);
	for (int i = 1; i <= most; ++i) {
		tree[i] = i;
	}
	return 0;
}
