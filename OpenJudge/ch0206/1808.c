#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define SIZE 200

char a[SIZE], b[SIZE];
int dp[2][SIZE];

int max(int a, int b) {
	return a > b ? a : b;
}

int main(int argc, char * argv[]) {
	while (~scanf("%s%s", a, b)) {
		memset(dp, 0, sizeof(dp));
		int i;
		int n = strlen(a), m = strlen(b);
		// 利用了滚动数组优化空间复杂度
		#define C i%2
		#define P (i-1)%2
		for (i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (a[i] == b[j]) dp[C][j] = max(dp[C][j], ((i > 0 && j > 0) ? dp[P][j-1] : 0) + 1);
				else dp[C][j] = max(dp[C][j], max(i > 0 ? dp[P][j] : 0, j > 0 ? dp[C][j-1] : 0));
			}
		}
		printf("%d\n", dp[P][m - 1]);
		memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b));
	}
	return 0;
}
