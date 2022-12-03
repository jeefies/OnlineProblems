#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

int main(int argc, char * argv[]) {
	static long long int dp[1001] = {0};

	int n;
	scanf("%d", &n);
	for (int i = 0; i <= n; i++) {
		dp[i] = 1;
		for (int l = 1; l <= i / 2; l++) {
			dp[i] += dp[l];
		}
	}
	printf("%lld\n", dp[n]);
	return 0;
}
