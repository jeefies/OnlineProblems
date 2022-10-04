#include <stdio.h>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

#define SIZE 202

int n;
int stones[SIZE];
int cache[SIZE];
int good[SIZE][SIZE] = {0};
int bad[SIZE][SIZE] = {0};
int maxn = INT_MIN;

int main(int argc, char * argv[]) {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> stones[i];
		stones[i + n] = stones[i];
	}
	
	cache[0] = 0;
	for (int i = 1; i <= n + n; i++) {
		cache[i] = stones[i - 1] + cache[i - 1];
	}
	
	for (int s = 0; s < n; s++)
	for (int l = 1; l <= n; l++) {
		for (int i = s; i < s + n - l + 1; i++) {
			int best = 0, worst = INT_MAX;
			
			int total = cache[i + l] - cache[i];
			
			for (int x = 1; x < l; x++) {
				worst = min(worst, bad[i][x + i] + bad[x + i][i + l] + total);
				best = max(best, good[i][x + i] + good[x + i][i + l] + total);
			}
			
			good[i][i + l] = best;
			bad[i][i + l] = worst == INT_MAX ? 0 : worst;
		}
	}
	
	int best = INT_MIN, worst = INT_MAX;
	for (int i = 0; i < n; i++) {
		best = max(best, good[i][i + n]);
		worst = min(worst, bad[i][i + n]);
	}
	cout << worst << endl
		<< best << endl;
	return 0;
}