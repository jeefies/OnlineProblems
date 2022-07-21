
/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/18/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <math.h>

int main() {
	int a, b, n;
	scanf("%d%d%d", &a, &b, &n);
	int sep = b - a;
	printf("%d\n", a + sep * (n - 1));
	return 0;
}
