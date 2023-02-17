#include <stdio.h>

const int N = 1e6 + 7;

long long a[N];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", a + i);
	}
	
	int x, y;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		if (x != 0)
			a[x] -= y;
	}
	
	for (int i = 1; i <= n; ++i) {
		printf("%lld ", a[i]);
	}
	
	return 0;
}