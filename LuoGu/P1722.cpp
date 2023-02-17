#include <iostream>
#include <algorithm>

using namespace std;
const int N = 3003, MOD = 100000007;

long long dp[N] = {1, 1};

int main() {
	int n;
	cin >> n;
	
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j < i; ++j)
			dp[i] = (dp[i] + dp[j] * dp[i - j - 1]); // % MOD;
	}
	
	cout << dp[n] << endl;
	return 0;
}
