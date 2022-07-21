/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/16/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <math.h>

int main() {
	double a, b, x, y;
	scanf("%lf%lf%lf%lf", &a, &b, &x, &y);
	double dx = a - x;
	double dy = b - y;
	printf("%.3f\n", sqrt(dx * dx + dy * dy));
	return 0;
}
