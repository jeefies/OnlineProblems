#warning 这是使用了空间压缩法的算法

#include <stdio.h>
#include <string.h>

int field[102];

int mmax(int a, int b) {
	if (a > b) return a;
	return b;
}

int main() {
	
	int n;
	scanf("%d", &n);
	while (n--) {
		memset(field, 0, sizeof(field));

		int R, C;
		scanf("%d%d", &R, &C);

		int tmp;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				scanf("%d", &tmp);

				if (j == 0) field[j] += tmp;
				else field[j] = tmp + mmax(field[j], field[j - 1]);
			}
		}

		printf("%d\n", field[C - 1]);
	}
}
