/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0113/03/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main() {
	double x = 0.0;
	double d = 1.0 / 8.0;
	char s[16] = {0};
	scanf("%s", s);

	for (int i = 2; i < strlen(s); i++) {
		x += d * (double)(s[i] - '0');
		d /= 8.0;
	}

	printf("%g\n", x);
}
