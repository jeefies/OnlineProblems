#include <stdio.h>
#include <algorithm>

#define N 100007

int n, a[N], b[N];

void read() {
	scanf("%d", &n);
	
	int v;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &v);
		b[v] = i + 1;
	}
	
	for (int i = 0; i < n; ++i) {
		scanf("%d", &v);
		a[i] = b[v];
	} 
}


// find first li[i] >= k, and replace it.
int * lowAt(int * li, int m, int k) {
	int i = -1, p = 1;
	while (p) {
		if (i + p <= m && li[i + p] < k) i += p, p <<= 1;
		else p >>= 1;
	}
	return li + i + 1;
}

int LIS() {
	static int lis[N], l = -1;
	for (int i = 0; i < n; ++i) {
		if (l == -1 || lis[l] < a[i]) {
			lis[++l] = a[i];
			continue;
		}
		int * low = lowAt(lis, l, a[i]);
		*low = a[i];
		// printf("a(i) = %d, lowAt %d, l to %d\n", a[i], low - lis, l);
	}
	return l + 1;
}

int main() {
	read();
	printf("%d\n", LIS());
	return 0;
}