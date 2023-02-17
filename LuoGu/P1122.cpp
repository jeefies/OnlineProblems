#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e4 + 7;

struct Edge {
	int to, next;
};

Edge edge[N * 2];
int n;
int head[N], tot = 0;
int w[N];

void add(int u, int v) {
	++tot;
	edge[tot].to = v, edge[tot].next = head[u], head[u] = tot; 
}

long long dp[N] = {0}, ans = 0;
int vis[N];
void work(int x) {
	vis[x] = 1;
	dp[x] = w[x];
	int y;
	for (int i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (!vis[y]) {
			work(y);
			dp[x] += dp[y];
		}
	}
	
	dp[x] = max(dp[x], 0ll);
}

int main() {
	scanf("%d", &n);
	int u, v;
	for (int i = 1; i <= n; ++i) scanf("%d", w + i);
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &u, &v);
		add(u, v), add(v, u);
	}
	
	work(1);
	for (int i = 1; i <= n; ++i) ans = max(ans, dp[i]);
	if (ans == 0) {
		ans = w[1];
		for (int i = 2; i <= n; ++i) ans = max(ans, (long long)w[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
