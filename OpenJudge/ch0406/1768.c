#include <stdio.h>

int N;
int matrix[102][102];

int mmax(int a, int b) {
	return a > b ? a : b;
}

int calcSum(int a, int b, int x, int y) {
	int r = matrix[x][y];

	if (a > 0)
		r -= matrix[a - 1][y];

	if (b > 0)
		r -= matrix[x][b - 1];

	if (a > 0 && b > 0)
		r += matrix[a - 1][b - 1];

	return r;
}

int main() {
	scanf("%d", &N);

	int maxn = -250;
	int tmp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &tmp);
			if (tmp > maxn) maxn = tmp;
			// calc partly sum
			if (j > 0) matrix[i][j] = tmp + matrix[i][j - 1];
			else matrix[i][j] = tmp;
		}
	}

	for (int j = 0; j < N; j++) {
		for (int i = 1; i < N; i++) {
			matrix[i][j] += matrix[i - 1][j];
		}
	}

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			for (int a = 0; a < x; a++) {
				for (int b = 0; b < y; b++) {
					maxn = mmax(maxn, calcSum(a, b, x, y));
				}
			}
		}
	}

	printf("%d\n", maxn);
	return 0;
}
