#include <stack>
#include <cstdio>
#include <iostream>

const long long N = 1e5 + 5;
long long n;
long long value[N] = {0};
long long sum[N] = {0};
long long ls[N], rs[N];

std::stack<long long> stk;
int main() {
	while (~scanf("%lld", &n)) {
		for (long long i = 1; i <= n; ++i) {
			scanf("%lld", value + i);
			sum[i] = sum[i - 1] + value[i];
		}
		
		for (long long i = 1; i <= n; ++i) {
			while (!stk.empty() && value[stk.top()] >= value[i]) stk.pop();
			ls[i] = stk.empty() ? 0 : stk.top();
			stk.push(i);
		}
		while (!stk.empty()) stk.pop();
		
		for (long long i = n; i >= 1; --i) {
			while (!stk.empty() && value[stk.top()] >= value[i]) stk.pop();
			rs[i] = stk.empty() ? n + 1 : stk.top();
			stk.push(i);
		}
		while (!stk.empty()) stk.pop();
		
		long long maxv = -1;
		long long ml = 1, mr = 1;
		for (long long i = 1; i <= n; ++i) {
			long long tv = value[i] * (sum[rs[i] - 1] - sum[ls[i]]);
			if (tv > maxv) {
				maxv = tv, ml = ls[i] + 1, mr = rs[i] - 1;
			}
		}
		
		printf("%lld\n%lld %lld\n", maxv, ml, mr);
	}
	return 0;
}
