#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>


#define BOOL char
#define TRUE 1
#define FALSE 0

int max(int a, int b) {
	return a > b ? a : b;
}

int n, maxdepth = 0;
BOOL mp[100][100] = {0};
BOOL toroot[100][100] = {0};
BOOL visited[100] = {0};
int data[100] = {0};

void search(int i, int depth) {
	data[depth] += 1;
	maxdepth = max(maxdepth, depth);
	for (int j = 1; j <= n; j++) {
		if (mp[i][j] == TRUE) {
			mp[j][i] = FALSE;
			toroot[j][i] = TRUE;
			search(j, depth + 1);
		}
	}
}

int main(int argc, char * argv[]) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		mp[x][y] = mp[y][x] = TRUE;
	}

	search(1, 1);
	int maxwidth = 0;
	for (int i = 1; i <= n; i++) {
		maxwidth = max(maxwidth, data[i]);
	}

	printf("%d\n%d\n", maxdepth, maxwidth);
	return 0;
}
