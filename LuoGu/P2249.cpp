#include <cstdio>

const int N = 1e6 + 3;

int a[N];
int n, q;

void find(int k) {
	int i = 0, p = 1;
	while (p) {
		if (i + p < n && a[i + p] < k) i += p, p <<= 1;
		else p >>= 1;
	}

	if (a[i + 1] == k) 
		printf("%d ", i + 1);
	else
		printf("-1 ");
}

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);

	int k;
	while (q--) {
		scanf("%d", &k);
		find(k);
	}
}
