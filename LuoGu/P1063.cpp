#include <stdio.h>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <algorithm>
#include <cstdint>

using namespace std;

#define SIZE 202
typedef int64_t i64;

int n;
i64 gems[SIZE];
i64 dp[SIZE][SIZE] = {0};
bool cached[SIZE][SIZE] = {false};

void search(int s, int e) {
	if (s + 2 >= e) {
		if (s + 2 == e)	dp[s][e] = gems[s] * gems[s + 1] * gems[s + 2];
		else dp[s][e] = 0;
		
		cached[s][e] = true;
	}
	
	if (cached[s][e]) return;
	
	i64 side = gems[s] * gems[e];
	i64 best = INT_MIN;
	
	for (int i = 1; i < e - s; i++) {
		search(s, s + i); search(s + i, e);
		best = max(best, dp[s][s + i] + dp[s + i][e] + side * gems[s + i]);
	}
	
	dp[s][e] = best;
	cached[s][e] = true;
}

int main(int argc, char * argv[]) {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> gems[i];
		gems[i + n] = gems[i];
	}
	gems[n + n] = gems[0];
	
	i64 maxn = INT_MIN;
	for (int i = 0; i < n; i++) {
		search(i, i + n);
		maxn = max(maxn, dp[i][i + n]);
	}
	
	cout << maxn << endl;
	
	return 0;
}