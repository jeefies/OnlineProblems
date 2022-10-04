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

typedef int64_t i64;

int t, m;
i64 costs[10001], values[10001];
i64 dp[int(1e7 + 1)] = {0};

int main(int argc, char * argv[]) {
	cin >> t >> m;
	for (int i = 0; i < m; i++) {
		scanf("%ld%ld", costs + i, values + i);
	}
	
	for (int i = 0; i < m; i++) {
		for (int j = costs[i]; j <= t; j++) {
			dp[j] = max(dp[j], dp[j - costs[i]] + values[i]);
		}
	}
	
	printf("%ld\n", dp[t]);
	
	return 0;
}