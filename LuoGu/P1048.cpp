#include <stdio.h>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <algorithm>
#include <cstring>

using namespace std;

int times[101];
int values[101];
int t, n;
/* normal version
// dp[i][j] within i mins pick first j plants' maximum value
int dp[1001][101] = {0};
*/
// dp[i] for the space compressed version
int dp[1001];

int main(int argc, char * argv[]) {
	cin >> t >> n;
	for (int i = 0; i < n; i++) {
		cin >> times[i] >> values[i];
	}
	memset(dp, 0, sizeof(dp));
	
	/* Normal version
	for (int j = 0; j < n; j++) {
		for (int i = 1; i <= t; i++) {
			// if don't pick
			int value = j > 0 ? dp[i][j - 1] : 0;
			// if can pick
			if (i >= times[j])
				value = max(value, dp[i - times[j]][j - 1] + values[j]);
			dp[i][j] = value;
		}
	}
	cout << dp[t][n - 1] << endl;
	*/
	
	// space compressed version
	for (int j = 0; j < n; j++) {
		for (int i = t; i > 0; i--) {
			// if don't pick
			int value = j > 0 ? dp[i] : 0;
			// if can pick
			if (i >= times[j])
				value = max(value, dp[i - times[j]] + values[j]);
			dp[i] = value;
		}
	}
	
	cout << dp[t] << endl;
	
	return 0;
}