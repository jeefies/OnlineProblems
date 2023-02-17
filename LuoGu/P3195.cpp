#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>

template<typename T>
inline void read(T &x) {
	register char tmp, f(x = 0);
	do if ((tmp = getchar()) == '-') f = 1; while (tmp < '0' || '9' < tmp);
	do x = x * 10 + (tmp ^ 48), tmp = getchar(); while ('0' <= tmp && tmp <= '9');
	if (f) x = -x;
}
template<typename T, typename ...Args>
inline void read(T &x, Args&...args) {
	read(x), read(args...);
}

const int N = 5e4 + 7;

int n, L;
long long sc[N], dp[N];

inline long long pf(long long x) {
	return x * x;
}

int main() {
	read(n, L);
	
	int ci;
	for (int i = 1; i <= n; ++i) read(ci), sc[i] = sc[i - 1] + ci;
	
	#define C(i, j) (sc[j] - sc[i - 1]) // [i, j]
	int last(1);
	for (int i = 1; i <= n; ++i) {
		dp[i] = LLONG_MAX;
		// printf("At %d:\n", i);
		for (int j = last; j <= i; ++j) {
			int x(i - j + C(j, i));
			// printf("\tby %d, x = %d\n", j, x);
			long long cur(dp[j - 1] + pf(x - L));
			if (cur < dp[i]) dp[i] = cur, last = j;
		}
		// printf("DP[%d] = %lld (last update by %d)\n", i, dp[i], last);
	}
	printf("%lld\n", dp[n]);
	return 0;
}