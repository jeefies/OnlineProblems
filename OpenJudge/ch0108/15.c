/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0108/15/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

int map[9][9];
int prev_map[9][9];

int birth(int x, int y);

int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			map[i][j] = 0;
			prev_map[i][j] = 0;
		}
	}

	int m, n;
	scanf("%d%d", &m, &n);
	map[4][4] = m;

	for (int i = 0; i < n; i++) {
		for (int dx = -i; dx <= i; dx++) {
			for (int dy = -i; dy <= i; dy++) {
				  prev_map[4 + dx][4 + dy] = map[4 + dx][4 + dy];
			}
		}

		for (int dx = -i; dx <= i; dx++) {
			for (int dy = -i; dy <= i; dy++) {
				birth(4 + dx, 4 + dy);
			}
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int birth(int x, int y) {
	int cnt = prev_map[x][y];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int ix = x - 1 + i, iy = y - 1 + j;
			map[ix][iy] += cnt;
		}
	}
}
