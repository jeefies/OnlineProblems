/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0106/03
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>


float cost[10] = {28.9, 32.7, 45.6, 78, 35, 86.2, 27.8, 43, 56, 65};

int main() {
	int c;
	float total = 0;
	for (int i = 0; i < 10; i++) {
		scanf("%d", &c);
		total += cost[i] * c;
	}

	printf("%.1f\n", total);
}
