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
#include <unistd.h>

int main() {
	int o, r = 0, isNeg = 0;
	scanf("%d", &o);
	if (o < 0) {
		isNeg = 1;
		o = -o;
	}

	while (o > 0) {
		r = r * 10 + o % 10;
		o /= 10;
	}

	if (isNeg) {
		r = -r;
	}
	printf("%d\n", r);
}
