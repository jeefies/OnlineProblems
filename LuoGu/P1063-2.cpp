#include <stdio.h>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <algorithm>

#define SIZE 202

using namespace std;
int n;
int gems[SIZE] = {0};
int dp[SIZE][SIZE] = {0};

int main(int argc, char * argv[]) {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> gems[i];
		gems[i + n] = gems[i];
	}
	gems[n + n] = gems[0];
	
	for (int s = 0; s < n; s++)
	for (int l = 1; l <= n; l++) {
		for (int i = s; i < s + n - l + 1; i++) {
			int side = gems[i] * gems[i + l];
			
			int best = 0;
			for (int x = 1; x < l; x++) {
				best = max(best, dp[i][i + x] + dp[i + x][i + l] + side * gems[i + x]);
			}
			
			dp[i][i + l] = best;
		}
	}
	int best = INT_MIN;
	for (int i = 0; i < n; i++) {
		best = max(best, dp[i][i + n]);
	}
	cout << best << endl;
	return 0;
}