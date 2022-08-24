#include <iostream>
#include <tuple>
#include <utility>
#include <queue>
#include <cstring>

using namespace std;

bool maze[202][202];
bool visited[202][202];

tuple<int, int, int> q[40005];
int head = 0, tail = 0;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int r, c;

int minroad(int sx, int sy, int tx, int ty) {
	q[tail++] = make_tuple(sx, sy, 0);

	while (head != tail) {
		int x, y, s;
		tie(x, y, s) = q[head++];

		if (x == tx && y == ty) {
			cout << s << endl;
			return 0;
		}

		maze[x][y] = true;

		for (int i = 0; i < 4; i++) {
			int cx = x + dx[i], cy = y + dy[i];

			if (0 <= cx && cx < r && 0 <= cy && cy < c && maze[cx][cy] == false && visited[cx][cy] == false) {
				q[tail++] = make_tuple(cx, cy, s + 1);
				visited[cx][cy] = true;
			}
		}
	}

	cout << "oop!" << endl;
	return 1;
}

int main() {
	int n;
	cin >> n;
	while (n-- > 0) {
		memset(maze, 0, sizeof(maze));
		memset(visited, 0, sizeof(maze));
		head = 0, tail = 0;

		int sx, sy, tx, ty;
		cin >> r >> c;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				char tmp;
				cin >> tmp;
				if (tmp == 'S') sx = i, sy = j;
				else if (tmp == 'E') tx = i, ty = j;
				else if (tmp == '#') maze[i][j] = true;
			}
		}

		minroad(sx, sy, tx, ty);
	}
}
