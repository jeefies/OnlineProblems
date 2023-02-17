#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>

const int N = 11;

typedef long long i64;

int num[N];

i64 f[N][N][N][N][2][2][2][2];

i64 dfs(int now, int pre, int ppre, int pppre, bool cnt, bool zero, bool limit, bool four, bool eight) {
	if (four && eight) return 0;
	if (now < 0) return cnt;
	if (!zero && ~f[now][pre][ppre][pppre][cnt][limit][four][eight]) return f[now][pre][ppre][pppre][cnt][limit][four][eight];
	
	int i(zero ? 1 : 0), ie(limit ? num[now] : 9);
	i64 res(0);
	for (; i <= ie; ++i) {
		// if (i == pre && pre == ppre) printf("at %d, val %d %d %d match!\n", now, i, pre, ppre);
		res += dfs(now - 1, i, pre, ppre, cnt | (i == pre && pre == ppre && ppre == pppre), false, limit && i == num[now], four || i == 4, eight || i == 8);
	}
	
	if (!zero) f[now][pre][ppre][pppre][cnt][limit][four][eight] = res;
	return res;
	
}

i64 solve(i64 x) {
	if (x < 1e10) return 0;
	
	int len(0);
	while (x) {
		num[len++] = x % 10, x /= 10;
	}
	
	memset(f, 0xFF, sizeof(f));
	return dfs(len - 1, 10, 10, 10, 0, true, true, false, false);
}

long long randInt() {
	static bool init(false);
	if (!init) srand(114514), init = true;
	long long x(0);
	while (x == 0) x = rand() % 10;
	for (int i(0); i < 10; ++i) {
		x = x * 10 + (rand() % 10);
	}
	return x;
}

int main() {
	i64 l, r;
	std::cin >> l >> r;
	std::cout << solve(r) - solve(l - 1) << '\n';
	return 0;
	
	for (int i = 1; i <= 100; ++i) {
		l = randInt(), r = randInt();
		if (l > r) std::swap(l, r);
		std::cout << solve(r) - solve(l - 1) << '\n';
	}
	return 0;
}