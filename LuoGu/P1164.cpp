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
int dp[100][10001] = {0};
int costs[100];

int main(int argc, char * argv[]) {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> costs[i];
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			int count = i > 0 ? dp[i - 1][j] : 0;
			if (j >= costs[i]) {
				count = max(count, dp[i - 1][j - costs[i]] + 1);
			}
			dp[i][j] = count;
		}
	}
	
	cout << dp[n - 1][m] << endl;
	return 0;
}