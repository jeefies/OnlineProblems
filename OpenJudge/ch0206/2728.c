#include <stdio.h>

int field[102][102];

int mmax(int a, int b) {
	if (a > b) return a;
	return b;
}

int main() {
	int n;
	scanf("%d", &n);
	while (n--) {
		int R, C;
		scanf("%d%d", &R, &C);
	
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				scanf("%d", &field[i][j]);
			}
		}
	
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (i == 0 && j == 0) continue;
				if (i == 0) field[i][j] = field[i][j] + field[i][j - 1];
				else if (j == 0) field[i][j] = field[i - 1][j] + field[i][j];
				else field[i][j] = field[i][j] + mmax(field[i - 1][j], field[i][j - 1]);
			}
		}
	
		printf("%d\n", field[R - 1][C - 1]);
	}
	return 0;
}
