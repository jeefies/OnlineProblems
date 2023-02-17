#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define N 50 + 3
#define T 2500

char mp[N][N];
int f[N][N][N];

int n, m, t;

void read() {
	memset(f, 0, sizeof(f));
	
	scanf("%d %d %d", &n, &m, &t);
	
	for (int i = 1; i <= n; ++i) {
		scanf("%s", mp[i] + 1);
		for (int j = 1; j <= m; ++j) {
			mp[i][j] += mp[i][j - 1] - '0';
		}
	}
}

#define g f[line]
#define pre mp[line]
void work(int line) {
	// g[i][j] 前i个数染j次最多粉刷的个数
	for (int i = 1; i <= m; ++i) {
		g[i][1] = max((int)pre[i], i - pre[i]);
	}
	
	// g[i][j] = max{g[k][j - 1] + max(f[i] - f[k], (i - k + 1) - (f[i] - f[k])}
	for (int j = 2; j <= m; ++j) {
		for (int i = j; i <= m; ++i) {
			for (int k = 0; k <= i; ++k) {
				int l = max(pre[i] - pre[k], (i - k) - (pre[i] - pre[k]));
				g[i][j] = max(g[i][j], g[k][j - 1] + l);
			}
		}
	}
	/*	
	printf("Res:\n");
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= i; ++j) {
			printf("%d ", g[i][j]);
		}
		puts("");
	}
	*/
}

int main() {
	read();
	for (int i = 1; i <= n; ++i) {
		work(i);
	}
	
	static int dp[T];
	for (int line = 1; line <= n; ++line) { // 行 
		for (int i = t; i; --i) { // 背包容量 
			for (int j = 1; j <= m; ++j) { // 涂的个数 
				if (i >= j) dp[i] = max(dp[i], dp[i - j] + g[m][j]);
				else break;
			}
		}		
	}
	
	printf("%d\n", dp[t]);
	return 0;
}
