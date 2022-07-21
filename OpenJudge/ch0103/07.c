/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/07/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
	double x, a, b, c, d;
	scanf("%lf%lf%lf%lf%lf", &x, &a, &b, &c, &d);
	printf("%.7f\n", x * x * x * a + x * x * b + x * c + d);
	return 0;
}
