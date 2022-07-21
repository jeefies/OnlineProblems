/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CAN 1
#define NO 0

int bx, by, mx, my;
long long map[25][25];

int set(int x, int y, int val);
long long get(int x, int y);

int main(){
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

	for (int j = 0; j <= by; j++) {
		for (int i = 0; i <= bx; i++) {
			map[0][0] = 1;
			if (get(i, j) == NO) continue;
			map[i][j] = get(i - 1, j) + get(i, j - 1);
		}
	}

	printf("%lld\n", map[bx][by]);

    return 0;
} 

int set(int x, int y, int val) {
	if (x < 0 || x >= 25 || y < 0 || y >= 25) return 1;
	map[x][y] = val;
	return 0;
}

long long get(int x, int y) {
	if (x < 0 || x >= 25 || y < 0 || y >= 25) return 0;
	return map[x][y];
}
