/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0106/12/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main() {
	int n;
	scanf("%d", &n);

	if (n < 64) {
		printf("%lu\n", (unsigned long)1 << n);
		return 0;
	}
}
