/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0108/23/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

int row, col;

int map[100][100];
int amap[100][100];

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

int cnt;

void printer(int x, int y, int stat) {
	if (cnt == 1) {
		printf("%d\n", map[x][y]);
		return;
	}
	if (stat == RIGHT) {
		while (x + 1 < row && amap[x+1][y] == 1)
			printf("%d\n", map[x][y], amap[x++][y] = 0, --cnt);
		printer(x, y, DOWN);
	} else if (stat == DOWN) {
		while (y + 1 < col && amap[x][y+1] == 1)
			printf("%d\n", map[x][y], amap[x][y++] = 0, --cnt);
		printer(x, y, LEFT);
	} else if (stat == LEFT) {
		while (x > 0 && amap[x-1][y] == 1)
			printf("%d\n", map[x][y], amap[x--][y] = 0, --cnt);
		printer(x, y, UP);
	} else {
		while (y > 0 && amap[x][y-1] == 1)
			printf("%d\n", map[x][y], amap[x][y--] = 0, --cnt);
		printer(x, y, RIGHT);
	}
}

int main() {
	scanf("%d%d", &row, &col);
	cnt = row * col;

	for (int y = 0; y < col; y++) {
		for (int x = 0; x < row; x++) {
			scanf("%d", &map[x][y]);
			amap[x][y] = 1;
		}
	}
	printer(0, 0, RIGHT);
}
