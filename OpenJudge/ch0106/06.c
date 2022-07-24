/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0106/06
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int road[10001];

int main() {
	int l, m;
	scanf("%d%d", &l, &m);

	for (int i = 0; i <= l; i++) road[i] = 1;

	for (int i = 0; i < m; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		for (int x = l; x <= r; x++) {
			road[x] = 0;
		}
	}

	int c = 0;
	for (int i = 0; i <= l; i++) {
		if (road[i] == 1) c++;
	}

	printf("%d\n", c);
}
