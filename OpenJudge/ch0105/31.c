/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0105/31
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

int main() {
	int m, n;
	scanf("%d%d", &n, &m);
	// On 1, Off 0
	int * lights = (int *)malloc(sizeof(int) * (n + 1));
	for (int i = 2; i < m; i++) {
		for (int j = i; j < n; j += i) {
			lights[j] = lights[j] == 0 ? 1 : 0;
		}
	}

	int is_first = 1;
	for (int i = 2; i < n; i++) {
		if (lights[i] == 0)
			if (is_first)
				is_first = 0;
			else
				printf(",");
			printf("%d", i);
	}
	free(lights);
}
