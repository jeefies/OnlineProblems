extern "C" {
	#include <cstdio>
	#include <cstring>
	#include <cstdlib>
	#include <climits>
}

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

int m, n;
int costs[25];
int imps[25];
int dp[30001] = {0};

int main(int argc, char * argv[]) {
	cin >> m >> n;
	for (int i = 0; i < n; i++) {
		cin >> costs[i] >> imps[i];
	}
	
	for (int i = 0; i < n - 1; i++) {
		for (int c = m; c > 0; c--) {
			if (c >= costs[i])
				dp[c] = max(dp[c], dp[c - costs[i]] + costs[i] * imps[i]);
		}
	}
	if (m >= costs[n - 1])
		dp[m] = max(dp[m], dp[m - costs[n - 1]] + costs[n - 1] * imps[n - 1]);
		
	cout << dp[m] << endl;
	return 0;
}