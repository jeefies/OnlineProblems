/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0108/10/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

int map[100][100];

int main() {
	int row, col;
	scanf("%d%d", &row, &col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	for (int j = 0; j < col; j++) {
		for (int i = 0; i < row; i++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}
