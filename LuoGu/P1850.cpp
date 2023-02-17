#include <iostream>
#include <cstring>
#include <algorithm>

using std::min;

const int V = 307, N = 3007;
const double DINF = 2e9;

int n, m, v, e;
int dis[V][V];
int c[N], d[N];
// dp[i][j][k]
// front i days, apply j times
// k 0 not apply, 1 apply!
double dp[N][N][2];
double k[N];

void floyd() {
	for (int k(1); k <= v; ++k) {
		for (int i(1); i <= v; ++i)
			for (int j(1); j < i; ++j)
				dis[j][i] = dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	}
}

int main() {
	register int i;
	memset(dis, 0x3F, sizeof(dis));
	scanf("%d %d %d %d", &n, &m, &v, &e);
	
	for (i = 1; i <= n; ++i) scanf("%d", c + i);
	for (i = 1; i <= n; ++i) scanf("%d", d + i);
	for (i = 1; i <= n; ++i) scanf("%lf", k + i);
	
	int a, b, w;
	for (i = 0; i < e; ++i) {
		scanf("%d %d %d", &a, &b, &w);
		dis[a][b] = dis[b][a] = min(dis[a][b], w);
	}
	for (i = 1; i <= v; ++i) {
		dis[i][i] = 0;
	} floyd();
	
	// set to INF
	for (i = 1; i <= n; ++i) {
		for (register int j = 0; j <= m; ++j)
			dp[i][j][0] = dp[i][j][1] = DINF;
	}
	// INIT DP
	dp[1][0][0] = dp[1][1][1] = 0;
	// BEGIN DP
	for (int i = 2; i <= n; ++i) {
		dp[i][0][0] = dp[i - 1][0][0] + dis[c[i - 1]][c[i]];
		
		// printf("dp[%d][%d][0/1] = (%lf, %lf)\n", i, 0, dp[i][0][0], dp[i][0][1]);
		
		for (int j(0), je(min(i, m)); j <= je; ++j) {
			int cc = c[i], pc = c[i - 1], cd = d[i], pd = d[i - 1];
			/*
			printf("\tat (i %d, j %d)\n", i, j);
			printf("\t\t{%d %d %d %d}\n", cc, pc, cd, pd);
			*/
			dp[i][j][0] = min(
				dp[i - 1][j][0] + dis[pc][cc], // prev not applied
				dp[i - 1][j][1] + k[i - 1] * dis[pd][cc] + (1 - k[i - 1]) * dis[pc][cc]
			);
			// printf("\t\tfrom {%lf, %lf}\n", dp[i - 1][j][0] + dis[pc][cc], dp[i - 1][j][1] + k[i - 1] * dis[pd][cd] + (1 - k[i - 1]) * dis[pc][cc]);
			
			if (j)
			dp[i][j][1] = min(
				dp[i - 1][j - 1][0] + k[i] * dis[pc][cd] + (1 - k[i]) * dis[pc][cc],
				dp[i - 1][j - 1][1] +
				k[i - 1] * k[i] * dis[pd][cd] + // both success
				k[i - 1] * (1 - k[i]) * dis[pd][cc] + // prev success, current failed
				(1 - k[i - 1]) * k[i] * dis[pc][cd] + // prev failed, current success
				(1 - k[i - 1]) * (1 - k[i]) * dis[pc][cc] // both failed
			);
			/*
			printf("\t\tfrom {%lf, %lf}\n", dp[i - 1][j - 1][0] + k[i] * dis[pc][cd] + (1 - k[i]) * dis[pc][cc], both);
			printf("dp[%d][%d][0/1] = (%lf, %lf)\n", i, j, dp[i][j][0], dp[i][j][1]);
			*/
		}
	}
	
	double res = DINF;
	for (int j(0); j <= m; ++j) {
		res = min(res, min(dp[n][j][0], dp[n][j][1]));
	}
	printf("%.2lf", res);
	return 0;
}