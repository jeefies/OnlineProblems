#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 1e5 + 7;

char __t[N], s[N<<1];

int P[N<<1];
void prepare(int n) {
	int M(0), R(0), p;
	for (int i(1); i < n; ++i) {
		p = i > R ? 1 : min(P[M * 2 - i], R - i + 1);
		while (s[i + p] == s[i - p]) ++p; // expand
		if (i + p - 1 > R) R = i + p - 1, M = i;
		P[i] = p;
	}
}

int lmax[N<<1], rmax[N<<1];
void process(int n) {
	// lmax[i], 右端点为i最多向左边延伸的长度(origin count)
	// rmax[i], 左端点为i最多向右边延伸的长度(origin count)
	for (int i = 1; i < n; ++i) {
		lmax[i + P[i] - 1] = max(lmax[i + P[i] - 1], P[i] - 1);
		rmax[i - P[i] + 1] = max(rmax[i - P[i] + 1], P[i] - 1);
	}
	
	// 所有的边界一定在 '#' 上！ 
	for (int i = 1; i < n; i += 2) {
		rmax[i] = max(rmax[i - 2] - 2, rmax[i]);
	}
	for (int i = n - 1; i > 0; i -= 2) {
		lmax[i] = max(lmax[i + 2] - 2, lmax[i]);
	}
}

void output(int n) {
	int ans(0);
	for (int i(1); i < n; i += 2) {
		if (lmax[i] && rmax[i]) ans = max(ans, lmax[i] + rmax[i]);
	}
	printf("%d\n", ans);
}

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	cin >> __t;
	int n = strlen(__t), i(0), j(2);
	s[0] = '^', s[1] = '#';
	for (; i < n; ++i) {
		s[j++] = __t[i], s[j++] = '#';
	} n = j;
	
	// printf("%s\n", s);
	
	prepare(n); // Manacher
	/*
	printf("Prepare ok\n");
	for (int i(1); i < n; ++i) {
		printf("%d ", P[i]);
	} printf("\n");
	*/
	process(n);
	output(n);
	return 0;
}
