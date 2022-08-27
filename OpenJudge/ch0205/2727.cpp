#include <iostream>
#include <queue>
#include <cstdio>
#include <tuple>

using namespace std;

int ox[4] = {1, 0, -1, 0};
int oy[4] = {0, 1, 0, -1};

char mp[25][25];
int m, n;

typedef tuple<int, int, int> step;
queue<step> pq;

// bool ok(int x, int y) {
// 	if (x < 0 || y < 0 || x >= m || y >= n || mp[x][y] == '#') return false;
// 	return true;
// }
// 
// bool stepin(int x, int y, int k) {
// 	if (ok(x-1, y)) pq.push(make_tuple(x-1, y, k));
// 	if (ok(x+1, y)) pq.push(make_tuple(x+1, y, k));
// 	if (ok(x, y-1)) pq.push(make_tuple(x, y-1, k));
// 	if (ok(x, y+1)) pq.push(make_tuple(x, y+1, k));
// }

void bfs(int cx, int cy, int dx, int dy) {

	mp[cx][cy] = '#';
	pq.push(make_tuple(cx, cy, 0));
	while (!pq.empty()) {
		int x, y, k;
		tie(x, y, k) = pq.front();
		pq.pop();

		if (x == dx && y == dy) {
			cout << k << endl;
			return;
		}
		
		mp[x][y] = '#';
		// stepin(x, y, k + 1);

		for (int i = 0; i < 4; i++) {
			int nx = x + ox[i], ny = y + oy[i];
			if (0 <= nx && nx < m && 0 <= ny && ny < n && mp[nx][ny] != '#') pq.push(make_tuple(nx, ny, k + 1));
		}
	}
	
	cout << -1 << endl;
}

int main() {
	while (true) {
		cin >> m >> n;
		if (m == 0 && n == 0) break;
		
		int cx, cy, dx, dy;
		for (int i = 0; i < m; i++) {
			// ignore '\n'
			// while (getchar() != '\n');
			
			for (int j = 0; j < n; j++) {
				// mp[i][j] = getchar();
				cin >> mp[i][j];
				if (mp[i][j] == '@') cx = i, cy = j;
				if (mp[i][j] == '*') dx = i, dy = j;
			}
		}
		
		bfs(cx, cy, dx, dy);

		while (!pq.empty()) {
			pq.pop();
		}
	}
	
	return 0;
}
