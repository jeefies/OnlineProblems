#include <iostream>
#include <algorithm>

using namespace std;
constexpr int N = 2000 + 3;
// dp for E
double dp[N][N], p;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int n, t;
	cin >> n >> p >> t;
	dp[0][0] = 1;
	
	/* Use E[i][j] to update others */
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (int i = 0; i < t; ++i) {
		for (int j = 0; j <= n; ++j) if (dp[i][j] > 1e-10) {
			if (j ^ n) dp[i + 1][j + 1] += dp[i][j] * p, dp[i + 1][j] += dp[i][j] * (1 - p);
			else dp[i + 1][j] += dp[i][j]; // j == n ????
		}
	}
	
	for (int i = 0; i <= t; ++i) {
		for (int j = 0; j <= n; ++j)
			printf("%.5lf ", dp[i][j]);
		printf("\n");
	} printf("\n");
	
	double res(0.0);
	for (int j = 0; j <= n; ++j) {
		res += dp[t][j] * j;
	}
	printf("%.6lf", res);
}