/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0105/22/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

int main() {
	int predict[12];
	for (int i = 0; i < 12; i++) {
		scanf("%d", &predict[i]);
	}

	int save = 0;
	int have = 0;
	int currentM = 0; // start from 0 end at 11
	while (have >= 0 && currentM < 12) {
		have += 300;
		have -= predict[currentM];
		while (have > 100) {
			have -= 100;
			save += 100;
		}
		++currentM;
	}

	if (have < 0) {
		printf("-%d\n", currentM);
	} else {
		printf("%.0f\n", (float)have + (float)save * 1.2);
	}
}
