#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20;

#define int long long

int n[N];
int f[N][N * 10][2][2];

int dfs(int now, bool zero, bool limit, int cnt, int target) {
	if (now < 0) return cnt;
	
	if (~f[now][cnt][zero][limit]) return f[now][cnt][zero][limit];
	
	int res(0), ie = limit ? n[now] : 9, cur = n[now];
	bool czero;
	for (int i(0); i <= ie; ++i) {
		czero = zero && !i;
		res += dfs(now - 1, czero, limit && i == cur, cnt + (!czero && i == target), target);
	}
	return f[now][cnt][zero][limit] = res;
}

int solve(int x, int target) {
	if (!x) return 0;
	
	int len(0);
	while (x) {
		n[len++] = x % 10, x /= 10;
	}
	
	memset(f, 0xFF, sizeof(f));

	return dfs(len - 1, true, true, 0, target);
}

signed main() {
	int l, r;
	scanf("%lld %lld", &l, &r);
	for (int target(0); target < 10; ++target) {	
		printf("%lld ", solve(r, target) - solve(l - 1, target));
	}
	return 0;
}