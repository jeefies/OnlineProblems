/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/05/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%.4f%\n", (double)b * 100 / (double)a);
	return 0;
}
