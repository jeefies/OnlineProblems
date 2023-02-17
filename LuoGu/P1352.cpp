#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 6e3 + 7;

int n, root;
struct Edge {
	int to, next;
}; 
Edge edge[N];
int head[N], tot = 0;
int w[N], par[N];

void add(int u, int v) {
	++tot;
	edge[tot] = {v, head[u]}, head[u] = tot;
}

void read() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", w + i);
	int u, v;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &u, &v);
		add(v, u);
		par[u] = v;
	}
	
	for (int i = 1; i <= n; ++i) {
		if (par[i] == 0) {
			root = i; break;
		}
	}
}

int dp[N][2];
void work(int x) {
	int y;
	dp[x][1] = w[x];
	for (int i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		work(y);
		dp[x][0] += max(dp[y][0], dp[y][1]);
		dp[x][1] += dp[y][0];
	}
}

int main() {
	read();
	work(root);
	printf("%d\n", max(dp[root][0], dp[root][1]));
	return 0;
}
