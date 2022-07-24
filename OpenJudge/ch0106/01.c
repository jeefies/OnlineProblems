/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 *  	Origin URL: http://noi.openjudge.cn/ch0106/01/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int nums[101];

int main() {
	int c;
	scanf("%d", &c);
	for (int i = 0; i < c; i++) {
		scanf("%d", nums + i);
	}

	int aim;
	scanf("%d", &aim);

	int sc = 0;
	for (int i = 0; i < c; i++) {
		if (nums[i] == aim) sc++;
	}

	printf("%d\n", sc);
}
