#include <stdio.h>
#include <string.h>

int path[102][102];

int max(int a, int  b) {
	if (a > b) return a;
	return b;
}

int main() {
	memset(path, 0, sizeof(path));

	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			scanf("%d", &path[i][j]);

			if (i == 0) continue;

			if (j == 0) path[i][j] += path[i - 1][j];
			else path[i][j] += max(path[i - 1][j], path[i - 1][j - 1]);
		}
	}

	int maxn = 0;
	for (int i = 0; i < n; i++) maxn = max(maxn, path[n - 1][i]);

	printf("%d\n", maxn);
}
