/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://ybt.ssoier.cn:8088/problem_show.php?pid=1258
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int steps[1000] = {0}, osteps[1000] = {0};

int max(int x, int y) {
	return x > y ? x : y;
}

int main() {
	int r;
	scanf("%d", &r);

	int tmp;
	for (int c = 1; c <= r; c++) {
		for (int i = 0; i < c; i++) {
			scanf("%d", &tmp);
			if (i == 0) steps[i] = osteps[i] + tmp;
			else steps[i] = max(osteps[i], osteps[i - 1]) + tmp;
		}

		for (int i = 0; i < c; i++) {
			osteps[i] = steps[i];
		}
	}

	int maxn = 0;
	for (int i = 0; i < r; i++)
		maxn = max(maxn, osteps[i]);

	printf("%d\n", maxn);
}
