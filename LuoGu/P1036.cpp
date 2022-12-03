#include <iostream>

bool isPrime(int x) {
	for (int i = 2; i * i <= x; ++i) {
		if (x % i == 0) return false;
	}
	return true;
} 

int n, k;
int ans = 0;
int a[20];

void srch(int i, int tot, int ck) {
	tot += a[i], ++ck;
	// printf("searching %d %d %d\n", i, tot, ck);
	if (ck == k && isPrime(tot)) ++ans;
	if (i == n || ck >= k) return;
	
	for (int j = i + 1; j < n; ++j) {
		srch(j, tot, ck);
	}
}

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; ++i) scanf("%d", a + i);
	
	for (int i = 0; i < n; ++i) srch(i, 0, 0);
	printf("%d\n", ans);
	return 0;
}
