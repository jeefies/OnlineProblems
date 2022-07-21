
/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/09/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
	double r;
	scanf("%lf", &r);

	double PI = 3.14159;

	printf("%.4lf %.4lf %.4lf", 2 * r, 2 * PI * r, PI * r * r);
}
