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
int dpmax[SIZE][SIZE] = {0};
int dpmin[SIZE][SIZE] = {0};
bool cached[SIZE][SIZE] = {false};

// 左闭右开
int rangesum(int s, int e) {
	static int cache[SIZE];
	static bool initialized = false;
	if (!initialized) {
		cache[0] = 0;
		for (int i = 1; i <= n + n; i++) {
			cache[i] = stones[i - 1] + cache[i - 1];
		}
		initialized = true;
	}
	
	return cache[e] - cache[s];
}

// 左闭右开
void search(int start, int end) {
	if (start + 1 == end) {
		dpmin[start][end] = dpmax[start][end] = 0;
		cached[start][end] = true;
	}
	
	if (cached[start][end]) return;
	
	int best = INT_MIN, worst = INT_MAX, total = rangesum(start, end);
	
	for (int i = 1; i < end - start; i++) {
		search(start, start + i);
		search(start + i, end);
		
		worst = min(worst, dpmin[start][start + i] + dpmin[start + i][end] + total);
		best = max(best, dpmax[start][start + i] + dpmax[start + i][end] + total);
	}
	
	dpmin[start][end] = worst;
	dpmax[start][end] = best;
	
	cached[start][end] = true;
}

int main(int argc, char * argv[]) {
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> stones[i];
		stones[i + n] = stones[i];
	}
	
	int minn = INT_MAX, maxn = INT_MIN;
	
	for (int i = 0; i < n; i++) {
		search(i, i + n);
		minn = min(minn, dpmin[i][i + n]);
		maxn = max(maxn, dpmax[i][i + n]);
	}
	
	cout << minn << endl
		<< maxn << endl;
	
	return 0;
}