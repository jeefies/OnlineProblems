/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P2066
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

int info[20][20] = {0};
int money[20][20] = {0};
int takes[20][20] = {0};

void print(int i, int m) {
	if (i > 0)
		print(i - 1, m - takes[i][m]);

	printf("%d %d\n", i + 1, takes[i][m]);
}

int main() {
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> info[i][j];
			money[i][j] = info[i][j];
			takes[i][j] = j;
		}
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			int maxn = INT_MIN;
			int take;
			for (int x = j; x >= 0; x--) {
				if (money[i - 1][j - x] + info[i][x] > maxn) {
					maxn = money[i - 1][j - x] + info[i][x];
					take = x;
				}
			}

			money[i][j] = maxn;
			takes[i][j] = take;
		}
	}

	cout << money[n - 1][m] << endl;

	print(n - 1, m);

	return 0;
}
