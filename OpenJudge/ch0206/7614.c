#include <stdio.h>

int area[100][100];

#define min(a,b) a<b?a:b

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &area[i][j]);
			if (i == 0 && j == 0) continue;
			if (i == 0) area[i][j] += area[i][j - 1];
			else if (j == 0) area[i][j] += area[i - 1][j];
			else area[i][j] += min(area[i][j - 1], area[i - 1][j]);
		}
	}

	printf("%d\n", area[n - 1][n - 1]);
	return 0;
}
