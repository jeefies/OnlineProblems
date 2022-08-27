#include <iostream>
#include <cstring>

using namespace std;

char mp[25][25];
int m, n;
int minstep = 1 << 30;

bool ok(int x, int y) {
	if (x < 0 || y < 0 || x >= m || y >= n || mp[x][y] == 1) return false;
	return true;
}

int findroad(int cx, int cy, int k) {
	if (mp[cx][cy] == 2) {
		minstep = min(minstep, k);
		return 0;
	}
	
	// set visited
	mp[cx][cy] = 1;
	
	++k;
	if (ok(cx + 1, cy)) findroad(cx + 1, cy, k);
	if (ok(cx - 1, cy)) findroad(cx - 1, cy, k);
	if (ok(cx, cy + 1)) findroad(cx, cy + 1, k);
	if (ok(cx, cy - 1)) findroad(cx, cy - 1, k);

	mp[cx][cy] = 0;

	return 0;
}

int main() {
	while (cin >> m >> n) {
		if (m == 0 && n == 0) break;
		memset(mp, 0, sizeof(mp));

		int cx, cy;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				char tmp;
				cin >> tmp;
				if (tmp == '@') cx = i, cy = j, mp[i][j] = 0;
				else if (tmp == '*') mp[i][j] = 2;
				else mp[i][j] = 1;
			}
		}
			
		findroad(cx, cy, 0);
		if (minstep == 1 << 30) minstep = -1;
		cout << minstep << endl;
		minstep = 1 << 30;
	}

	return 0;
}
