#include <stdio.h>

int n[1002], dp[1002] = {0};

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", n + i);
		dp[i] = n[i];
	}

	int maxn = dp[0];
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (n[j] < n[i])
				dp[i] = max(dp[i], dp[j] + n[i]);
		}
		maxn = max(maxn, dp[i]);
	}
	
	printf("%d\n", maxn);
}
