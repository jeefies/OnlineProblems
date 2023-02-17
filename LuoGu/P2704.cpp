#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

#define to(i) (1<<(i))
#define mark(x,i) ((x) | to(i))
#define unmark(x, i) ((x) & ~to(i))
#define revmark(x, i) ((x) ^ to(i))
#define ismarked(x, i) (((x)>>i) & 1)

#define N 100 + 7

int n, m;
int lines[N] = {0};
static int dp[N][N][N];

int main() {
	std::ios::sync_with_stdio(false);
	cin >> n >> m;
	
	char tmp;
	for (int i(0); i ^ n; ++i) {
		for (int j(0); j ^ m; ++j) {
			cin >> tmp;
			if (tmp == 'H') lines[i] = mark(lines[i], j);
		}
		// printf("Line %d: %#x\n", i, lines[i]);
	}

	static int sta[N], cnt[N], sitc(0);
	for (int i(0); i < to(m); ++i) {
		if (i & (i << 1) || i & (i << 2)) continue;
		sta[sitc] = i;
		for (int j = i; j; j ^= j & -j) ++cnt[sitc];
		++sitc;
	}
	
	/*
	for (int i(0); i < sitc; ++i) {
		printf("%#x(%d) ", sta[i], cnt[i]);
	} puts("");
	*/
	
	for (int l(0); l < n; ++l) { // l for line
		auto cur = dp[l], prev = l ? dp[l - 1] : dp[n];
		for (int k(0); k < sitc; ++k) { // k for l status
			if (sta[k] & lines[l]) continue; // situation not fit
			for (int j(0); j < sitc; ++j) { // j for prev status
				if (sta[k] & sta[j]) continue;
				for (int i(0); i < sitc; ++i) { // i for prev prev status
					if (sta[k] & sta[i] || sta[j] & sta[i]) continue;
					cur[k][j] = max(cur[k][j], prev[j][i] + cnt[k]);
				}
			}
		}
	}
	
	int res(0);
	auto last = dp[n - 1];
	for (int i(0); i < sitc; ++i) for (int j(0); j < sitc; ++j)
		res = max(res, last[i][j]);
	cout << res << endl;
	return 0;
}