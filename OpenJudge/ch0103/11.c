
/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/11/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
	double a, b;
	scanf("%lf%lf", &a, &b);
	int s = a / b;
	printf("%g\n", a - (double)s * b);
	return 0;
}
