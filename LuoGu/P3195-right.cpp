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
typedef long long ll;

inline ll pow2(ll x) { return x * x; }

inline ll a(int i) {
	return i + sc[i];
}
inline ll b(int j) {
	return j + 1 + sc[j] + L;
}
inline ll y(int j) {
	return dp[j] + pow2(b(j));
}
inline ll x(int j) {
	return b(j);
}

inline double slope(int i, int j) {
	return (double)(y(i) - y(j)) / (x(i) - x(j));
}

int main() {
	read(n, L);
	
	int ci;
	for (int i = 1; i <= n; ++i) {
		read(ci), sc[i] = sc[i - 1] + ci;
	}
	
	// dp[j - 1] + pow2(b) = 2a * b + dp[i] - pow2(a)
	static int Q[N];
	int head(1), tail(1);
	for (int i = 1; i <= n; ++i) {
		while (head < tail && slope(Q[head], Q[head + 1]) < 2 * (double)a(i)) ++head;
		int j = Q[head];
		// printf("From %d\n", j);
		dp[i] = dp[j] + pow2(a(i) - b(j));
		// printf("dp[%d] = %lld\n", i, dp[i]);
		while (head < tail && slope(i, Q[tail] - 1) < slope(Q[tail - 1], Q[tail])) --tail;
		Q[++tail] = i;
	}

	printf("%lld\n", dp[n]);
	return 0;
}