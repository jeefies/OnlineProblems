/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/13/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
	int x;
	scanf("%d", &x);
	for (int i = 0; i < 3; i++) {
		printf("%d", x % 10);
		x /= 10;
	}
	return 0;
}
