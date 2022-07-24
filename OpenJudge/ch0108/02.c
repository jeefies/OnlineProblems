/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 *  	Origin URL: http://noi.openjudge.cn/ch0108/02/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

int main() {
	int n, i, j;
	scanf("%d%d%d", &n, &i, &j);
	
	printf("(%d,1)", i);
	for (int y = 2; y <= n; y++) {
		printf(" (%d,%d)", i, y);
	}
	printf("\n");

	printf("(1,%d)", j);
	for (int x = 2; x <= n; x++) {
		printf(" (%d,%d)", j, x);
	}
	printf("\n");

	int x = i, y = j;
	while (x > 1 && y > 1) {
		x--;
		y--;
	}
	// printf("(%d,%d)", x, y);
	while (x <= n && y <= n) {
	// while (x < n && y < n) {
		printf("(%d,%d) ", x++, y++);
		// printf(" (%d,%d)", ++x, ++y);
	}
	putchar('\n');

	x = i;
	y = j;
	while (x < n && y > 1) {
		x++;
		y--;
	}
	// printf("(%d,%d)", x, y);
	while (x >= 1 && y <= n) {
	// while (x > 1 && y < n) {
		printf("(%d,%d) ", x--, y++);
		// printf(" (%d,%d)", --x, ++y);
	}
	putchar('\n');
}
