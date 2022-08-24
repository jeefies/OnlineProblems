#include <stdio.h>

int main() {
	int n;
	while (scanf("%d", &n)) {
		int tmp, sum = 0, maxn = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &tmp);
			sum += tmp;
			maxn = maxn > sum ? maxn : sum;
		}
	
		if (sum - maxn > maxn) printf("%.1f\n", sum / 2.0);
		else printf("%.1f\n", maxn / 2.0);
	}
	return 0;
}
