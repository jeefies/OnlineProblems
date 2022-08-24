#include <stdio.h>
#include <string.h>

int bds[100];
int dp[100];

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int main() {
	int k;
	scanf("%d", &k);

	while (k--) {
		int n;
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%d", bds + i);
		}

		int maxn = 0;
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if (bds[j] < bds[i])
					dp[i] = max(dp[i], dp[j] + 1);
			}
			maxn = max(maxn, dp[i]);
		}
		 
		// reverse
		for (int l = 0, r = n - 1; l < r; l++, r--) {
			int tmp = bds[l];
			bds[l] = bds[r];
			bds[r] = tmp;
		}

		memset(dp, 0, sizeof(dp));
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if (bds[j] < bds[i])
					dp[i] = max(dp[i], dp[j] + 1);
			}
			maxn = max(maxn, dp[i]);
		}

		printf("%d\n", maxn + 1);
	}
}
