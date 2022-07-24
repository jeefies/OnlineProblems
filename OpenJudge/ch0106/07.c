/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		http://noi.openjudge.cn/ch0106/07
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int subs[3000];

int main() {
	int n;
	scanf("%d", &n);

	int a, b;
	scanf("%d", &a);
	for (int i = 1; i < n; i++) {
		scanf("%d", &b);
		subs[abs(a - b)] = 1;
		a = b;
	}
	for (int i = 1; i < n; i++) {
		if (subs[i] == 0) {
			printf("Not jolly\n");
			return 0;
		}
	}

	printf("Jolly\n");
	return 0;
}
