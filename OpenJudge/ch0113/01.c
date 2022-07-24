/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0113/01/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int preProcessChar(char x) {
	if ('a' <= x && x <= 'z')
		return x - 'a' + 10;
	if ('0' <= x && x <= '9')
		return x - '0';
	if ('A' <= x && x <= 'Z')
		return x - 'A' + 10;
}

char preProcessNum(char x) {
	if (0 <= x && x < 10)
		return x + '0';
	else
		return x + 'A' - 10;
}

int main() {
	int a, b;
	char n[80] = {0};

	scanf("%d%s%d", &a, n, &b);
	long ten = 0;
	for (int i = 0; i < strlen(n); i++) {
		ten = ten * a + preProcessChar(n[i]);
	}
	// printf("%ld\n", ten);
	
	char r[80] = {0};
	int i = 0;
	do {
		r[i++] = ten % b;
		ten /= b;
	} while (ten > 0);

	for (i = i - 1; i >= 0; i--) {
		printf("%c", preProcessNum(r[i]));
		// printf("%d\n", r[i]);
	}
	printf("\n");
}
