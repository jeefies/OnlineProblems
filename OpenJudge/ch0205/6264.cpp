#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

// visited true, not false
bool mp[105][105];
int m, n, cx, cy, dx, dy;

int ox[4] = {0, 1, 0, -1}, oy[4] = {1, 0, -1, 0};

bool ok(int x, int y) {
	if (x < 0 || y < 0 || x >= n || y >= m || mp[x][y]) return false;
	return true;
}

void stepIn(queue<tuple<int, int, int>> & q, int x, int y, int c) {
	for (int i = 0; i < 4; i++) {
		int cx = x + ox[i], cy = y + oy[i];
		if (ok(cx, cy))
			q.push(make_tuple(cx, cy, c + 1));
	}
}

int gout() {
	queue<tuple<int, int, int>> q;

	q.push(make_tuple(cx, cy, 0));

	while (!q.empty()) {
		int x, y, c;
		tie(x, y, c) = q.front();
		q.pop();

		// printf("visit %d %d step %d\n", x, y, c);

		if (x == dx && y == dy) {
			cout << c << endl;
			return 0;
		}

		mp[x][y] = true;
		stepIn(q, x, y, c);
	}
}

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char tmp;
			cin >> tmp;
			mp[i][j] = false;
			if (tmp == 'S') cx = i, cy = j;
			else if (tmp == 'T') dx = i, dy = j;
			else if (tmp == '#') mp[i][j] = true;
		}
	}

	gout();
}
