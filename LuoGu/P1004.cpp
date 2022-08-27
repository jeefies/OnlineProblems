#include <iostream>
#include <cstring>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

int mp[11][11];
int cache[11][11][11][11];

int N;

int pprint() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%-3d ", mp[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int dfs(int a, int b, int x, int y) {
	if (a == N && b == N && x == N && y == N) {
		return mp[N][N];
	}

	// if (a > N || b > N || x > N || y > N) return 0;
	
	if (cache[a][b][x][y] != -1) return cache[a][b][x][y];
	
	int cur = mp[a][b];
	// 标记清0
	int on = mp[a][b];
	mp[a][b] = 0;
	// 然后在加xy, 防止重复
	cur += mp[x][y];

	int best = 0;
	// ab向右，xy向下
	if (b < N && x < N)
		best = max(best, dfs(a, b+1, x+1, y) + cur);
	
	// ab，xy都向下
	if (a < N && x < N)
		best = max(best, dfs(a+1, b, x+1, y) + cur);

	// ab,xy都右
	if (b < N && y < N)
		best = max(best, dfs(a, b+1, x, y+1) + cur);

	// ab下，xy右
	if (a < N && y < N)
		best = max(best, dfs(a+1, b, x, y+1) + cur);
	// 回溯
	mp[a][b] = on;

	cache[a][b][x][y] = best;
	return best;
}

int main() {
	cin >> N;

	// clear, pre-process
	memset(mp, 0, sizeof(mp));
	// 如果cache设为0的话，当第一次搜索没有搜到任何数的时候，best为0……
	// 后果只是陷入死循环而已
	for (int a = 0; a <= N; a++)
		for (int b = 0; b <= N; b++)
			for (int c = 0; c <= N; c++)
				for (int d = 0; d <= N; d++)
					cache[a][b][c][d] = -1;

	int nx, ny, n;
	while (true) {
		cin >> nx >> ny >> n;
		if (nx + ny + n == 0) break;
		mp[nx][ny] = n;
	}

	// pprint();

	cout << dfs(1, 1, 1, 1) << endl;
	return 0;
}
