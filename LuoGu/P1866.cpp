#include <cstdio>
#include <algorithm>

const int N = 50, MAXN = 1e9 + 7;
int a[N];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", a + i);
	std::sort(a, a + n);
	long long ans = a[0];
	for (int i = 1; i < n; ++i)
		ans = (ans * (a[i] - i)) % MAXN;
	printf("%lld\n", ans);
}
