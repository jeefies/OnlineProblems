#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100 + 7;

struct Edge {
	int to, next, w;
};

Edge edge[N * 2];
int n;
int head[N], tot = 0;

void add(int u, int v, int w) {
	++tot;
	edge[tot].to = v, edge[tot].next = head[u], edge[tot].w = w, head[u] = tot; 
}

// f[u][j] u内留j个树枝的最多
// for s \in Son(u)
// 	f[u][j] = max(f[u][j], f[u][k] + f[s][j - k - 1] + w(u, s))
// 0 <= j - k - 1 <= siz[s]
// 
int f[N][N]; 
int siz[N];
void work(int x, int fa) {
	int y, w;
	siz[x] = 1;
	for (int i = head[x]; i; i = edge[i].next) {
		y = edge[i].to, w = edge[i].w;
		if (y == fa) continue;
		work(y, x);
		siz[x] += siz[y];
		
		for (int j = siz[x] - 1; j; --j) {
			for (int k = 0; k < siz[y]; ++k) { // j - k > 0
				if (j == k) break;
				f[x][j] = max(f[x][j], f[x][j - k - 1] + f[y][k] + w);
			}
			// printf("f[%d][%d] to %d\n", x, j, f[x][j]);
		}
	}
}

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	int u, v, w;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d %d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	
	work(1, 0);
	printf("%d", f[1][q]);
	return 0;
}
