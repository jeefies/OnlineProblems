/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1281
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
	
int books[500], wn[500][500] = {0}, cost[500][500];

void print(int i, int j) {
	if (j == 0) return;
	print(i - wn[i][j], j - 1);

	printf("%d %d\n", i - wn[i][j] + 1, i);
}

int main() {

	int m, k;
	cin >> m >> k;

	for (int i = 0; i < m; i++) {
		cin >> books[i];
		if (i > 0) books[i] += books[i - 1];
		cost[1][i] = books[i];
	}

	for (int i = 2; i <= k; i++) {
		for (int j = 0; j < m; j++) {
			int minn = cost[i - 1][j];
			int minw = 0;

			for (int w = 1; w < j; w++) {
				int newtake = books[j] - books[j - w];
				int resttake = cost[i - 1][j - w];

				int take = max(newtake, resttake);
				if (take <= minn) {
					minw = w;
					minn = take;
				}
			}
		}
	}

	print(m - 1, k);
	return 0;
}
