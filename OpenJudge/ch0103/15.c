/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/15/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <math.h>

int main() {
	int n, x, y;
	scanf("%d%d%d", &n, &x, &y);
	int notFull = (y + x - 1) / x;
	printf("%d\n", n - notFull);
	return 0;
}
