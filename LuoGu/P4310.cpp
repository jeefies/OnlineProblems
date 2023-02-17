#include <iostream>
#include <algorithm>

using namespace std;

#define lowbit(i) (i&-i)
#define kth(i) (lowbit(i) % 37)

int main() {
	int n;
	scanf("%d", &n);
	static int dp[37];
	
	int res = 0;
	for (int m, x, t, i = 0; i < n; ++i) {
		scanf("%d", &x), m = 0;
		t = x;
		for (; x; x -= lowbit(x)) {
			m = max(m, dp[kth(x)] + 1);
		} res = max(res, m);
		for (; t; t -= lowbit(t)) {
			dp[kth(t)] = m;
		}
	}
	printf("%d\n", res);
	return 0;
}