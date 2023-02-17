#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int len;
int n[20];
int f[20][20][2][2];

int dfs(int now, int pre, bool zero, bool limit) {
	if (now < 0) return !zero;
	if (~f[now][pre][zero][limit]) return f[now][pre][zero][limit];
	
	int res(0), ie(limit ? n[now] : 9);
	for (int i(0); i <= ie; ++i) {
		if (!zero && i - pre < 2 && pre - i < 2) continue; // pre exists and division smaller than 2
		res += dfs(now - 1, i, zero && !i, limit && i == n[now]);
	}
	
	return f[now][pre][zero][limit] = res;
}

int solve(int x) {
	if (!x) return 0;
	
	for (len = 0; x; x /= 10, ++len)
		n[len] = x % 10;
		
	memset(f, 0xFF, sizeof(f));
	return dfs(len - 1, 0, true, true);
}

int main() {
	int l, r;
	scanf("%d %d", &l, &r);
	printf("%d\n", solve(r) - solve(l - 1));
	return 0;
}