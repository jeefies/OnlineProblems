#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <deque>

using namespace std;

const int N = 6000 + 7;

int n;
int h[N];
deque<int> g[N];

int f[N][2];
inline void dp(int x) {
	f[x][1] = h[x];
	for (const int y : g[x]) {
		dp(y);
		f[x][0] += max(f[y][0], f[y][1]);
		f[x][1] += f[y][0];
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", h + i);
	}
	
	int c, p;
	static int fa[N];
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &c, &p);
		g[p].push_back(c);
		fa[c] = p;
	}
	
	int root;
	for (root = 1; root <= n; ++root) {
		if (!fa[root]) break;
	}
	
	dp(root);
	printf("%d\n", max(f[root][0], f[root][1]));
	return 0;
}