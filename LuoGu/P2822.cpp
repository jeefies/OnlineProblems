#include <iostream>
#include <algorithm>
#include <cmath>

int k;
const int N = 2e3 + 1, MAXN = 1e9 + 7;
long long C[N][N], ans[N][N];

void init() {
	C[0][0] = C[1][0] = C[1][1] = 1;
	
	for (int i = 2; i <= 2000; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = (C[i-1][j-1] + C[i-1][j]) % k;
			if (!C[i][j]) ++ans[i][j];
		}
	}
	
	// ¶þÎ¬Ç°×ººÍ 
	for (int i = 2; i <= 2000; ++i) {
		for (int j = 1; j <= i; ++j) {
			ans[i][j] += ans[i-1][j] + ans[i][j-1] - ans[i-1][j-1];
		}
		ans[i][i + 1] = ans[i][i];
	}
}

void proc() {
	static int n, m;
	scanf("%d %d", &n, &m);
	
	printf("%lld\n", ans[n][std::min(m, n)]);
}

int main() {
	int T;
	scanf("%d %d", &T, &k);
	init();
	while (T--) proc();
}
