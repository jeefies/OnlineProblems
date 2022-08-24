#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

char mp[50][50];

int ox[4] = {0, 1, 0, -1};
int oy[4] = {1, 0, -1, 0};

queue< tuple<int, int, int> > tq;

int go(int dx, int dy) {

	int k = 0;
	tq.push(make_tuple(0, 0, 1));
	while (!tq.empty()) {
		int x, y, k;
		tie(x, y, k) = tq.front();
		tq.pop();

		if (x == dx && y == dy) {
			cout << k << endl;
			return 0;
		}

		mp[x][y] = '#';

		for (int i = 0; i < 4; i++) {
			int cx = x + ox[i], cy = y + oy[i];
			if (mp[cx][cy] == '.')
				tq.push(make_tuple(cx, cy, k+1));
		}
	}

	return 0;
}

int main() {
	int r, c;
	cin >> r >> c;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> mp[i][j];
		}
	}

	go(r - 1, c - 1);
}
