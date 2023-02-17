#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <climits>

using std::deque;

template<typename T>
inline T max(T x, T y) {
	return x < y ? y : x;
}

template<typename T>
inline T min(T x, T y) {
	return x > y ? y : x;
}

const int N = 1e5 + 7;

int n, m;
static int h[N] = {INT_MAX}, pre[N];
static int dp[N];

typedef long long data;
struct Node {
	data lazy, maxn;
} nodes[N * 6];

#define lp(p) (p<<1)
#define rp(p) (lp(p)|1)
#define ct(p) nodes[p]
#define maxn(p) ct(p).maxn
#define lazy(p) ct(p).lazy
#define update(p) (maxn(p) = min(maxn(lp(p)), maxn(rp(p))))

inline void sync(int p) {
	if (lazy(p)) {
		maxn(p) += lazy(p);
		maxn(lp(p)) += lazy(p), lazy(lp(p)) = lazy(p);
		maxn(rp(p)) += lazy(p), lazy(rp(p)) = lazy(p);
		lazy(p) = 0;
	}
}

// useless!
inline void build(int cl = 0, int cr = N, int p = 1) {
	if (cl == cr) {
		ct(p) = {0, h[cl]};
		return;
	}
	int mid = (cl + cr) >> 1;
	build(cl, mid), build(mid + 1, cr);
	update(p);
}

inline void add(int l, int r, data val, int cl = 0, int cr = N, int p = 1) {
	if (l <= cl && cr <= r) {
		maxn(p) += val;
		lazy(p) += val;
		return;
	}
	
	sync(p);
	int mid = (cl + cr) >> 1;
	if (l <= mid) add(l, r, val, cl, mid, lp(p));
	if (mid < r) add(l, r, val, mid+1, cr, rp(p));
	update(p);
}

inline data query(int l, int r, int cl = 0, int cr = N, int p = 1) {
	if (l <= cl && cr <= r) {
		return maxn(p);
	} else if (cl == cr) return 0;
	
	sync(p);
	int mid = (cl + cr) >> 1;
	data ans = LLONG_MAX;
	if (l <= mid) ans = query(l, r, cl, mid, lp(p));
	if (mid < r) ans = min(ans, query(l, r, mid + 1, cr, rp(p)));
	update(p);
	return ans;
}

int main() {
	scanf("%d %d", &n, &m);
	
	#define sh(i, j) (pre[j] - pre[i - 1]) // [i, j]
	for (int i = 1; i <= n; ++i) scanf("%d", h + i), pre[i] = pre[i - 1] + h[i];
	
	deque<int> q;
	
	#define ft() (q.empty() ? 0 : q.front())
	#define bk() (q.empty() ? 0 : q.back())
	
	for (int l(1), i = 1; i <= n; ++i) {
		printf("\nPOPING:\n");
		// pop invalid nodes
		while (sh(l + 1, i) > m) {
			++l;
			while (!q.empty() && q.front() <= l) q.pop_front();
		}
		printf("\nINSERTING:\n");
		// insert cuurent height
		while (!q.empty() && h[q.back()] <= h[i]) {
			int b = q.back(); q.pop_back();
			add(bk() + 1, b, -h[b]);
			printf("add(%d, %d, %d)\n", bk() + 1, b, -h[b]);
		}
		add(bk() + 1, i, h[i]);
		printf("add(%d, %d, %d)\n", bk() + 1, i, h[i]);
		q.push_back(i);
		printf("\nQUERY(%d, %d)\n", l, i - 1);
		if (l < i) dp[i] = query(l, i - 1);
		else dp[i] = dp[i - 1] + h[i];
		add(i, i, dp[i]);
		printf("dp[%d] to %d\n", i, dp[i]);
	}
	return 0;
}