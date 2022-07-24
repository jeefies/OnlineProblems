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

int main() {
	int a, b;
	scanf("%d%d", &a, &b);

	if (a < b) {
		int tmp = b;
		b = a; a = tmp;
	}
	int x;
	while (1) {
		x = a % b;
		if (x == 0) break;
		a = b;
		b = x;
	}
	printf("%d\n", b);
}
