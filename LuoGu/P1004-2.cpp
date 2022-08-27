#include <iostream>
#include <cstring>

using namespace std;

int mp[12][12];

int maxn = 0;

// 第一层用搜索，第二次用dp

int second() {
	int dp[12][12];
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i < 12; i++) {
		for (int j = 1; j < 12; j++) {
			dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]) + mp[i][j];
		}
	}

	return dp[11][11];
}


void first(int x, int y, int n) {
	if (x == 11 && y == 11) {
		n += second();
		maxn = max(n, maxn);
		return;
	}

	// 超出边界
	if (x > 11 || y > 11) return;

	// if (n != 0) { printf("x, y, n : %d %d %d\n", x, y, n); }

	// 标记
	int on = mp[x][y];
	n += on;
	mp[x][y] = 0;
	// 向右或向下
	
	if (x < 11) first(x + 1, y, n);
	if (y < 11) first(x, y + 1, n);

	// 回溯
	mp[x][y] = on;
}

int main() {
	int t; cin >> t;

	memset(mp, 0, sizeof(mp));

	int nx, ny, n;
	while (true) {
		cin >> nx >> ny >> n;
		if (nx + ny + n == 0) break;
		mp[nx][ny] = n;
	}

	first(0, 0, 0);

	cout << maxn << endl;
	return 0;
}
