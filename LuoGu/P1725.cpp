#include <iostream>
#include <algorithm>
#include <deque>
#include <cstring>
#include <cmath>

#define NDEBUG

using namespace std;

const int N = 2e5 + 10;

int n, l, r;
int v[N], dp[N];

void prtDP() {
	for (int i = 0; i <= n; i++)
		printf("%d ", dp[i]);
	putchar('\n');
}

int main() {
	scanf("%d %d %d",  &n, &l, &r); // 5 2 3
	for (int i = 0; i <= n; i++) scanf("%d", v + i);
	// for (int i = 0; i <= n; i++) printf("v[%d] = %d\n", i, i[v]);
	int k = r - l; // 1
	
	memset(dp, 0xC0, sizeof(dp));
	deque<int> dq;
	for (int i = l; i <= r; i++) dp[i] = v[i];
	
	int maxv = 0xC0C0C0C0;
	for (int i = l; i <= n; i++) {
		while (dq.size() && dq.front() < i - k) dq.pop_front();
		while (dq.size() && dq.back() <= dp[i]) dq.pop_back();
		dq.push_back(dp[i]);
		
		#ifndef NDEBUG
		printf("Area[%d, %d] max val %d\n", i - k, i, dq.front());
		#endif
		
		int target = i + l;
		if (target >= l + l && target <= n) dp[target] = v[target] + dq.front();
		if (target + l > n) maxv = max(maxv, dq.front() + (target > n ? 0 : v[target]));
		#ifndef NDEBUG
		printf("DP[%d] set to %d\n", target, dp[target]);
		putchar('\t'); prtDP();
		#endif
	}
	cout << maxv << endl;
	return 0;
}
