/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		This is just a bad solution.
 * 		Because even though the idea is right, but the cost is too much.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CAN 1
#define NO 0

int bx, by, mx, my;
int map[25][25];

int set(int x, int y, int val);
int get(int x, int y);
int go(int x, int y);

int arrive_c = 0;

int main() {
	memset(map, NO, 25 * 25);
	scanf("%d%d%d%d", &bx, &by, &mx, &my);

	for (int i = 0; i <= bx; i++) {
		for (int j = 0; j <= by; j++) {
			map[i][j] = CAN;
		}
	}

	// Set no steps
	set(mx, my, 0);
	set(mx + 2, my + 1, NO);
	set(mx + 2, my - 1, NO);
	set(mx + 1, my + 2, NO);
	set(mx + 1, my - 2, NO);
	set(mx - 1, my + 2, NO);
	set(mx - 1, my - 2, NO);
	set(mx - 2, my + 1, NO);
	set(mx - 2, my - 1, NO);

	printf("%d\n", go(0, 0));
}

int set(int x, int y, int val) {
	if (x < 0 || x >= 25 || y < 0 || y >= 25) return 1;
	map[x][y] = val;
	return 0;
}

int get(int x, int y) {
	if (x < 0 || x >= 25 || y < 0 || y >= 25) return 0;
	return map[x][y];
}

int go(int x, int y) {
	set(x, y, NO);
	// 可以到达，回退到分岔状态
	if (x == bx && y == by) {
		set(x, y, CAN);
		printf("Arrive %d\n", ++arrive_c);
		return 1;
	}

	int count = 0;
	// 如果右方可以走
	if (get(x + 1, y) == CAN) {
		count += go(x + 1, y);
	}

	// 如果下方可以
	if (get(x, y + 1) == CAN) {
		count += go(x, y + 1);
	}
	

	// 状态回退
	set(x, y, CAN);
	return count;
}
