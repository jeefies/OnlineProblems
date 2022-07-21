/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0101/09/
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
	char c = getchar();

	for (int i = -2; i <= 2; i++) {
		for (int j = 0; j < abs(i); j++) {
			putchar(' ');
		}
		for (int j = 0; j < (5 - abs(i) * 2); j++) {
			putchar(c);
		}
		putchar('\n');
	}
}
