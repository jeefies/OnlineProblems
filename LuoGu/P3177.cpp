#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <utility>

using namespace std;

const int N = 2e3 + 7;

typedef long long data;
struct Edge {
	int to, next, w;
} edge[N]; int head[N], tot = 0;
inline void add(int u, int v, int w) {
	edge[++tot] = {v, head[u], w}, head[u] = tot;
}

int n, k;

void read() {
	scanf("%d %d", &n, &k);
	
	int u, v, w;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d %d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
}

int siz[N], fa[N], w[N];
void preDP(int x, int par) {
	siz[x] = 1, fa[x] = par;
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y == par) continue;
		w[y] = edge[i].w;
		preDP(y, x);
		siz[x] += siz[y];
	}
}

data f[N][N];
void dp(int x) {
	f[x][1] = w[x];
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y == fa[x]) continue;
		dp(y);
		
		for (i)
	}
}

int main() {
	read();
	int root = (n + 1) / 2;
	preDP(root, 0);
	
	printf("root: %d\n", root);
	for (int i = 1; i <= n; ++i) {
		printf("node %d: w = %d, siz = %d\n", i, w[i], siz[i]);
	}
	
	// printf("%lld\n", f[root][k]);
}