#include <iostream>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <cstring>

#define NDEBUG

using namespace std;
const long long N = 5e5 + 2e3 + 10;
const long long INF = 0x3FFFFFF0FF00;

long long n, d, w;
struct XS {
	long long x, s;
	bool operator < (const XS & r) const {
		return x < r.x;
	}
	
	XS() {
		x = s = 0;
	}
};
XS xs[N];
static long long dp[N];
void prtDP() {
	for (long long i = 0; i < n; i++)
		printf("%d ", dp[i]);
	putchar('\n');
}

long long valid(long long g) {
	for (long long i = 0; i <= n; i++) dp[i] = -INF;
	
	long long k = g * 2 + 1;
	long long l = max(1ll, d - g), r = d + g;
	deque<long long> que;
	#ifndef NDEBUG
	printf("l, r = %d, %d; k = %d\n", l, r, k);
	#endif
	for (long long i = 0; i <= n; i++) {
		if (xs[i].x < l) continue;
		if (xs[i].x > r) break;
		dp[i] = xs[i].s;
		if (dp[i] >= w) return true;
	}
	
	// 单调栈维护范围是[xs[i].x - r, xs[i].x - l]的最大值
	long long le = 0, i = 1; // 0 是 {0, 0} 
	for (i = 1; i < n; i++) {
		while (que.size() && xs[que.front()].x < xs[i].x - r) que.pop_front(); // 清理<xs[i].x -r的脏东西 
		
		// 寻找范围最右侧的点 
		while (xs[le + 1].x + l <= xs[i].x) {
			++le;
			if (dp[le] == -INF) continue; // le其实是无法达到的 
			if (xs[le].x + r < xs[i].x) continue; // 跳过区间之间的空隙 
			while (que.size() && dp[le] >= dp[que.back()]) que.pop_back(); que.push_back(le);
		}
		if (xs[le].x + r < xs[i].x) continue; // 没有可以转移过来的东西 
		
		while (que.size() && dp[le] >= dp[que.back()]) que.pop_back(); que.push_back(le);
		#ifndef NDEBUG
		printf("%d transform from TOP %d (place %d)\n", i, dp[que.front()], que.front());
		#endif
		if (que.size()) dp[i] = max(dp[i], xs[i].s + dp[que.front()]);
		#ifndef NDEBUG
		printf("dp[%d] set to %d\n", i, dp[i]);
		#endif
		if (dp[i] >= w) return true;
	} 
	return false;
}

signed main() {
	// freopen("P3957_3.in", "r", stdin);
	 
	scanf("%lld %lld %lld", &n, &d, &w);
	for (long long i = 1; i <= n; i++) {
		scanf("%lld %lld", &xs[i].x, &xs[i].s);
	}
	
	long long l = 0, r = xs[n].x;
	if (!valid(r)) {
		cout << -1 << endl;
		return 0;
	}
	
	long long ans = -1;
	while (l <= r) {
		#ifndef NDEBUG
		printf("Searching [%d, %d]\n", l, r);
		#endif
		long long mid = (l + r) / 2;
		if (valid(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	
	cout << ans << endl;
	return 0;
}
