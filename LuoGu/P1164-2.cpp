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
#include <map>

using namespace std;

int main(int argc, char * argv[]) {
	int n, m;
	cin >> n >> m;
	static int dishes[100];
	for (int i = 0; i < n; i++) {
		cin >> dishes[i];
	}
	
	// init processing array
	static int dp[10001] = {1};
	for (int i = 1; i < 10001; i++) dp[i] = -1;
	
	for (int i = 0; i < n; i++) {
		for (int j = m; j >= dishes[i]; j--) {
			if (dp[j - dishes[i]] != -1) 
				dp[j] = dp[j] == -1 ? dp[j - dishes[i]] : dp[j] + dp[j - dishes[i]];
		}
	}
	
	cout << dp[m] << endl;
	
	return 0;
}