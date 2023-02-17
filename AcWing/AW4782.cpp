#include <stdio.h>

#define N 1007

int n, k;
int a[N];

int quickSelect(int l, int r, int k) {
	if (l + 1 == r) {
		return a[l];
	}
	
	int lp = l, rp = r - 1, key = a[lp];
	while (lp < rp) {
		while (lp < rp && a[rp] >= key)
			--rp;
		a[lp] = a[rp];
		
		while (lp < rp && a[lp] <= key)
			++lp;
		a[rp] = a[lp];
	}
	
	// mid = lp
	a[lp] = key;
	if (lp == k) return key;
	else if (lp < k) return quickSelect(lp + 1, r, k);
	else return quickSelect(l, lp, k);
	
	printf("Fuck you!\n");
	return -1; // never reached!
}

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	
	printf("%d\n", quickSelect(1, n + 1, n + 1 - k));
	return 0;
}