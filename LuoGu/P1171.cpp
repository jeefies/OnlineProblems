#include <iostream>
#include <algorithm>
#include <cstring>

using std::min;

#define to(i) (1<<(i))
#define mark(x,i) ((x) | to(i))
#define unmark(x, i) ((x) & ~to(i))
#define revmark(x, i) ((x) ^ to(i))
#define ismarked(x, i) (((x)>>i) & 1)

#define N 20

int mp[N][N];
int dp[N][to(N)];

int main() {
	memset(dp, 0x5F, sizeof(dp));
	dp[0][to(0)] = 0;
	
	int n;
	scanf("%d", &n);
	
	for (int i(0); i < n; ++i) {
		for (int j(0); j < n; ++j)
			scanf("%d", mp[i] + j);
	}
	// last target
	int target = to(n) - 1;
	for (int sta(1); sta <= target; sta += 2) {
		for (int to = 0; to < n; ++to) {
			if (!ismarked(sta, to)) continue;
			int fromSta = revmark(sta, to);
			for (int from(0); from < n; ++from) {
				if (to == from || !ismarked(sta, from)) continue;
				dp[to][sta] = min(dp[to][sta], dp[from][fromSta] + mp[from][to]);
			}
		}
	}
	
	int res = 0x7F7F7F7F;
	for (int end(0); end < n; ++end) {
		res = min(res, dp[end][target] + mp[end][0]);
	}
	printf("%d\n", res);
	return 0;
}