#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 2e3 + 7, MOD = 1e5 + 3;
int dp[N];

int main() {
	cin.tie(0)->sync_with_stdio(false);

	int a, b, c, d, k;
	cin >> a >> b >> c >> d >> k;

	// 反转了一下图形
#define h(i) (i <= c ? d : b + d)
	// init dp
	// for (int i = 0; i <= a + c; ++i) dp[i][0] = 1;
	dp[0] = 1;
	// main loop
	for (int i = 1; i <= a + c; ++i) {
		int ike = min(k, h(i));
		for (int ik = ike; ik; --ik)
			dp[ik] = (dp[ik] + (long long)dp[ik - 1] * (h(i) - ik + 1)) % MOD;
	}

	cout << dp[k];
	return 0;
}
