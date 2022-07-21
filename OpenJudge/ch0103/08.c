/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/08/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
	double f;
	scanf("%lf", &f);

	printf("%.5lf\n", 5 * (f - 32) / 9);
	return 0;
}
