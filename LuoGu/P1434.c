#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

int r, c;
int mp[100][100];
int cache[100][100];

int max(int a, int b) {
	return a > b ? a : b;
}

int cdfs(int i, int j, int prev) {
	// can not reach to here
	if (prev <= mp[i][j]) return -1;
	// already searched
	if (cache[i][j] >= 0) return cache[i][j];

	int cur = mp[i][j];
	int best = 0;

	// left
	if (i > 0) best = max(best, cdfs(i - 1, j, cur));
	// right
	if (i + 1 < r) best = max(best, cdfs(i + 1, j, cur));
	// down
	if (j + 1 < c) best = max(best, cdfs(i, j + 1, cur));
	// up
	if (j > 0) best = max(best, cdfs(i, j - 1, cur));

	best += 1;
	cache[i][j] = best;
	return best;
}

int main(int argc, char * argv[]) {
	memset(cache, 0xF0, sizeof(cache));
	scanf("%d%d", &r, &c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
			scanf("%d", mp[i] + j);
	}

	int maxn = INT_MIN;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
			maxn = max(maxn, cdfs(i, j, INT_MAX));
	}
	printf("%d\n", maxn);
	return 0;
}
