#include <iostream>
#include <queue>
#include <tuple>
#include <utility>

using namespace std;

int maze[5][5];
pair<int, int> mazeParent[5][5];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void print(int x, int y) {
	if (x == y && x == 0) {
		cout << "(0, 0)" << endl;
		return;
	}

	int px, py;
	tie(px, py) = mazeParent[x][y];
	print(px, py);
	printf("(%d, %d)\n", x, y);
}

bool go(int x, int y) {
	queue<pair<int, int>> q;
	q.push(make_pair(0, 0));

	while (!q.empty()) {
		int x, y;
		pair<int, int> parent;
		tie(x, y) = parent = q.front();
		q.pop();

		if (x == 4 && y == 4) {
			print(4, 4);
			return 0;
		}

		maze[x][y] = 1;

		for (int i = 0; i < 4; i++) {
			int cx = x + dx[i], cy = y + dy[i];
			if (cx >= 0 && cx < 5 && 0 <= cy && cy < 5 && maze[cx][cy] == 0) {
				q.push(make_pair(cx, cy));
				mazeParent[cx][cy] = parent;
			}
		}
	}
}

int main() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> maze[i][j];
		} 
	}

	go(0, 0);
}
