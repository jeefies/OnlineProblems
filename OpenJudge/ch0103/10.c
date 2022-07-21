
/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/10/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
	float a, b;
	scanf("%f%f", &a, &b);
	printf("%.2f\n", a * b / (a + b));
	return 0;
}
