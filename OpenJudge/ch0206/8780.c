#include <stdio.h>
#include <string.h>

int booms[16];

int dp[16];

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int main() {
	int n;
	scanf("%d", &n);

	memset(dp, 0, sizeof(dp));

	for (int i = 0; i < n; i++)
		scanf("%d", booms + i);

	int maxn = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (booms[i] <= booms[j])
				dp[i] = max(dp[i], dp[j] + 1);
		}
		maxn = max(maxn, dp[i]);
	}

	printf("%d\n", maxn + 1);
}
