/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0106/13
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int len;
char num[35];

int try_mod(int x) {
	int r = 0;
	for (int i = 0; i < len; i++)
		r = (r * 10 + num[i]) % x;

	return r;
}

int main() {
	scanf("%s", num);
	len = 34;
	while (len > 0 && num[len] == 0) --len;
	++len;

	for (int i = 0; i < len; i++) {
		num[i] -= '0';
	}

	int c = 0;
	for (int i = 2; i < 10; i++) {
		if (try_mod(i) == 0) {
			c++;
			printf("%d ", i);
		}
	}
	if (c == 0) printf("none");
}
