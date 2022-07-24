/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 *  	Origin URL: http://noi.openjudge.cn/ch0106/02
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main() {
	int apples[10];
	for (int i = 0; i < 10; i++) {
		scanf("%d", apples + i);
	}

	int height;
	scanf("%d", &height);

	int c = 0;
	for (int i = 0; i < 10; i++) {
		if (apples[i] <= height + 30) c++;
	}

	printf("%d\n", c);
}
