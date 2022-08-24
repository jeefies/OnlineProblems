#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

char mp[30][30];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int blacks(int x, int y) {
	if (x < 0 || y < 0 || mp[x][y] != '.') return 0;

	mp[x][y] = '#';

	int c = 1;
	for (int i = 0; i < 4; i++) {
		c += blacks(x + dx[i], y + dy[i]);
	}

	return c;
}

int main() {
	int w, h;
	while (cin >> w >> h && w != 0 && h != 0) {
		memset(mp, 0, sizeof(mp));
	
		int cx, cy;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> mp[i][j];
				if (mp[i][j] == '@') cx = i, cy = j, mp[i][j] = '.';
			}
		}
	
		cout << blacks(cx, cy) << endl;
	}
	return 0;
}
