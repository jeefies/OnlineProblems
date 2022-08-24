#include <stdio.h>
#include <iostream>

int main() {
	int n;
	while (std::cin >> n) {
		int tmp, sum = 0, maxn = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &tmp);
			sum += tmp;
			maxn = maxn > tmp ? maxn : tmp;
		}

		// printf("sum, maxn: %d %d\n", sum, maxn);
	
		if (sum - maxn > maxn) printf("%.1f\n", sum / 2.0);
		else printf("%.1f\n", (float)(sum - maxn));
	}
	return 0;
}
