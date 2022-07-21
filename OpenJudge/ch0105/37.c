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
	int m, n, x;
	scanf("%d%d%d", &m, &n, &x);
	
	while (1) {
		int usex = (m + n - 1) / n;
		x -= usex;
		if (x < 0) break;
		n += m / n;
	}
	printf("%d", n);
}
