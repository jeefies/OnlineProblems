/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/12/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
	double r;
	scanf("%lf", &r);
	printf("%0.2lf", r * r * r * 3.14 * 4 / 3);
	return 0;
}
