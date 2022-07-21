/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0102/09/
 * 		I don't know what does the the question means, but giving this to change a number to 0 or 1
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <stdio.h>

int main() {
	int x;
	scanf("%d", &x);
	printf("%d", x == 0 ? 0 : 1);
}
