/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0106/05
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main() {
	int people[4] = {0};

	int n;
	scanf("%d", &n);

	int age;
	for (int i = 0; i < n; i++) {
		scanf("%d", &age);
		if (age > 60) people[3]++;
		else if (age > 35) people[2]++;
		else if (age > 18) people[1]++;
		else people[0]++;
	}

	for (int i = 0; i < 4; i++) {
		printf("%.2f%\n", people[i] * 100 / (float)n);
	}
}
