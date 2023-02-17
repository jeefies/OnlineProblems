#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 300 + 7;

struct Edge {
	int to, next;
};

Edge edge[N * 2];
int n, m;
int head[N], tot = 0;
int w[N];

void add(int u, int v) {
	++tot;
	edge[tot].to = v, edge[tot].next = head[u], head[u] = tot;
}

// dp[u][j] 以u为根的树上选j门课的最大学分
// dp[u][0] = 0
// dp[u][j] = max{dp[u][j - k - 1] + dp[s][k] + w[u]}
// k in [0, siz[s]]
// j - k - 1 in [0, siz[j]]
int dp[N][N];
int siz[N];
void work(int x, int par) {
	int y;
	siz[x] = 1;
	for (int i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (y == par) continue;
		work(y, x);
		// printf("\t! Work %d ok\n", y);
		siz[x] += siz[y];
		
		// 注意这里是没有加上自己在所有子树中选 j 个 
		for (int j = siz[x] - 1; j; --j) {
			// siz[y] < siz[x]
			for (int k = 0; k <= siz[y]; ++k) {
				if (j >= k) dp[x][j] = max(dp[x][j], dp[x][j - k] + dp[y][k]);
				else break;
				// printf("dp[%d][%d] to %d (k = %d)\n", x, j, dp[x][j], k);
			}
		}
	}
	
	for (int j = siz[x]; j; --j) {
		dp[x][j] = dp[x][j - 1] + w[x];
		// printf("dp[%d][%d] final to %d\n", x, j, dp[x][j]);
	}
}

int main() {
	scanf("%d %d", &n, &m);
	int v, s;
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &v, &s);
		add(i, v), add(v, i);
		w[i] = s;
	}
	
	work(0, -1);
	/*
	for (int x = 0; x <= n; ++x) {
		printf("siz[%d] == %d\n", x, siz[x]);
		for (int j = 0; j <= siz[x]; ++j)
			printf("%d ", dp[x][j]);
		puts("");
	}
	*/
	printf("%d\n", dp[0][m + 1]);
	return 0;
}
/*
5 4
0 7
3 20
1 1
1 10
3 25
*/
