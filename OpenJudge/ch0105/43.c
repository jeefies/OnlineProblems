/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

int valid(int x) {
	for (int i = 2; i * i < x; i++) {
		if (x % i == 0) return 0;
	}
	return 1;
}

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 2; i < n; i++) {
		if (n % i == 0 && valid(i)) {
			printf("%d\n", n / i);
			break;
		}
	}
	return 0;
}
