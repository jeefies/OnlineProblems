#include <stdio.h>
#include <string.h>

#define int long long

const int N = 1e6 + 7;

int n, m;
int r[N], d[N], s[N], j[N];
long long dif[N];

void fill(int k) {
	static int lastk = 0;
	
	if (lastk < k) {
		for (int i = lastk + 1; i <= k; ++i) {
			dif[s[i]] += d[i];
			dif[j[i] + 1] -= d[i];
		}
	} else {
		for (int i = lastk; i > k; --i) {
			dif[s[i]] -= d[i];
			dif[j[i] + 1] += d[i];
		}
	}
	
	lastk = k;
}

bool valid(int k) {
	if (k == 0) return true;
	fill(k);
	
	int v = 0;
	for (int i = 1; i <= n; ++i) {
		v += dif[i];
		if (v > r[i]) return false;
	}
	
	return true;
}

signed main() {
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= n; ++i) {
		scanf("%d", r + i);
	}
	
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", d + i, s + i, j + i);
	}
	
	if (valid(m)) {
		printf("0\n");
		return 0;
	}
	
	int i = 0, p = 1;
	while (p) {
		if (i + p <= m && valid(i + p)) i += p, p *= 2;
		else p /= 2;
	}
	
	printf("-1\n%d\n", i + 1);
	
	return 0;
}