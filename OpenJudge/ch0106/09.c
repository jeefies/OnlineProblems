/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0106/09
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int ab[1001];

int main() {
	int n, t;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", ab + i);
	}

	int x = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		x += ab[i] * t;
	}

	printf("%d\n", x);
}
