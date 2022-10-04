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

#define SIZE 100000

int n, w;
int values[SIZE], weights[SIZE], numbers[SIZE];
int dp[2][40000] = {0};

int main(int argc, char * argv[]) {
	cin >> n >> w;
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", values + i, weights + i, numbers + i);
	}
	
	int lineNo = 0;
	
	for (int i = 0; i < n; i++) {
		for (int c = numbers[i]; c; c--) {
			for (int v = 1; v <= w; v++) {
				int ev = lineNo > 0 ? dp[(lineNo - 1) % 2][v] : 0;
				if (v >= weights[i]) {
					ev = max(ev, dp[(lineNo - 1) % 2][v - weights[i]] + values[i]);
				}
				dp[lineNo % 2][v] = ev;
			}
			++lineNo;
		}
	}
	
	cout << dp[(lineNo - 1) % 2][w] << endl;
	return 0;
}