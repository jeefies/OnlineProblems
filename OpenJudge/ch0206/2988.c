#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>


int min(int a, int b) {
	return a < b ? a : b;
}

int main(int argc, char * argv[]) {
	int k;
	scanf("%d", &k);
	for (int datai = 0; datai < k; datai++) {
		static char a[1002], b[1002];
		memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b));

		scanf("%s%s", a + 1, b + 1);
		int n = strlen(a + 1), m = strlen(b + 1);

		static int dp[1002][1002];
		for (int i = 0; i <= n; i++) {
			dp[i][0] = i;
		}
		for (int j = 0; j <= m; j++) {
			dp[0][j] = j;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				dp[i][j] = min(INT_MAX, dp[i-1][j-1] + 1);
				if (a[i] == b[j]) dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
				else dp[i][j] = min(dp[i][j], min(dp[i-1][j] + 1, dp[i][j-1] + 1));
			}
		}

		printf("%d\n", dp[n][m]);
	}
	return 0;
}
