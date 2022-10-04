#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#warning 数据范围是100000，RE总比WA好看一点
#define SIZE 1000

int a[SIZE], b[SIZE];
int dp[2][SIZE];

#warning 最多只能过一半的数据，没有优化，复杂的是O(n^2)

int max(int a, int b) {
	return a > b ? a : b;
}

int main(int argc, char * argv[]) {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", a+i);
	for (int i = 0; i < n; i++)
		scanf("%d", b+i);

	int i;
	// 利用了滚动数组优化空间复杂度
	#define C i%2
	#define P (i-1)%2
	for (i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i] == b[j]) dp[C][j] = max(dp[C][j], ((i > 0 && j > 0) ? dp[P][j-1] : 0) + 1);
			else dp[C][j] = max(dp[C][j], max(i > 0 ? dp[P][j] : 0, j > 0 ? dp[C][j-1] : 0));
		}
	}
	printf("%d\n", dp[P][n - 1]);
	return 0;
}
