/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://ybt.ssoier.cn:8088/problem_show.php?pid=1261
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>

int n, map[100][100] = {0}, dp[100] = {0}, prev[100] = {0};

int printPrev(int vn) {
	if (vn != 0)
		printPrev(prev[vn]);
	printf("%d ", vn + 1);
}

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		dp[i] = INT_MAX;
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);
	}

	dp[0] = 0;

	for (int j = 1; j < n; j++) {
		for (int i = 0; i < n; i++) {
			if (map[i][j] != 0 && dp[i] + map[i][j] < dp[j]) {
				dp[j] = dp[i] + map[i][j];
				prev[j] = i;
			}
		}
	}

	printf("minlong=%d\n", dp[n - 1]);
	printPrev(n - 1);
}
