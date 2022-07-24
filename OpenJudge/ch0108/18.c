/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0108/18/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

int main() {
	int a;
	scanf("%d", &a);

	int first0 = -1, last0 = -1;
	int tmp = 0;
	for (int i = 0; i < a * a; ++i) {
		scanf("%d", &tmp);
		if (tmp == 0) {
			if (first0 < 0) {
				first0 = i;
			}
			last0 = i;
		}
	}

	if (first0 == -1) {
		printf("0\n");
		return 0;
	}
	int lx = first0 % a, ly = first0 / a;
	int rx = last0 % a, ry = last0 / a;
	int area = (rx - lx - 1) * (ry - ly - 1);
	printf("%d\n", area);
	return 0;
}
