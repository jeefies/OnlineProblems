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

int v, n;
int spaces[30];

int main(int argc, char * argv[]) {
	cin >> v >> n;
	for (int i = 0; i < n; i++) {
		cin >> spaces[i];
	}
	
	static int dp[20000];
	for (int i = 0; i <= v; i++) dp[i] = 0;
	
	for (int i = 0; i < n; i++) {
		for (int j = v; j > 0; j--) {
			if (j >= spaces[i])
				dp[j] = max(dp[j], dp[j - spaces[i]] + spaces[i]);
		}
	}
	cout << v - dp[v] << endl;
	return 0;
}