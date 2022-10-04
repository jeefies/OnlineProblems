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


int main(int argc, char * argv[]) {
	int n, target;
	cin >> n >> target;

	static i64 coins[25];
	for (int i = 0; i < n; i++) {
		scanf("%ld", coins + i);
	}
	
	static i64 dp[10001] = {0};
	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int v = coins[i]; v <= target; v++) {
			if (dp[v - coins[i]]) {
				dp[v] = dp[v] + dp[v - coins[i]];
			}
		}
	}
	
	printf("%ld\n", dp[target]);
	return 0;
}