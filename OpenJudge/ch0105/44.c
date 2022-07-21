/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

int main() {
	int x;
	scanf("%d", &x);

	int * nums = (int *)malloc(sizeof(int) * x);
	nums[0] = 2;
	int len = 1;
	int valid = 0;
	int i = 3;
	while (len < x) {
		valid = 1;
		for (int j = 0; j < len; j++) {
			if (i % nums[j] == 0) {
				valid = 0;
				break;
			}
		}
		if (valid) {
			// printf("%d %d\n", i, len);
			nums[len++] = i;
		}
		i++;
	}
	printf("%d\n", nums[x - 1]);
	free(nums);
}
