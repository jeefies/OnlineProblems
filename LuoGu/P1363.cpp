#include <stack>
#include <iostream>

using namespace std;

const int N = 1510;
int n, m;
char mp[N * 3][N * 3];
bool vis[N * 3][N * 3];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct point {
	int x, y;
};

stack<point> stk;
int ox, oy;
bool getData() {
	if (scanf("%d %d", &n, &m) < 0) return false;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cin >> mp[n + i][m + j];
			for (int ki = 0; ki < 3; ki++)
				for (int kj = 0; kj < 3; kj++)
					mp[n * ki + i][m * kj + j] = mp[n + i][m + j];
					
			if (mp[n + i][m + j] == 'S') 
				ox = n + i, oy = m + j, 
				mp[n + i][m + j] == '.',
				stk.push({n + i, m + j}); 
		} 
	}
}

bool canOut() {
	while (!stk.empty()) {
		point & pt = stk.top();
		int x = pt.x, y = pt.y;
		stk.pop();
		char cc = mp[x][y];
		
		if (
			x < 0 || x >= n * 3 || y < 0 || y >= m * 3 || // 出界
			cc == '#' || vis[x][y] // 走不动 
		) continue;
		
		if (cc == 'S')
			return true;
		
		vis[x][y] = true;		
		for (int k = 0; k < 4; k++)
			stk.push({x + dx[k], y + dy[k]});
	}
	return false;
}

int main() {
	while (getData()) {
		printf("%s\n", canOut() ? "Yes" : "No");
	}
}
