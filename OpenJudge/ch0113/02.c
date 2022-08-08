/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		origin URL: http://noi.openjudge.cn/ch0113/02/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
	int w;
	scanf("%d", &w);

	w = (w + 13 - 1) % 7; // 获取13号的星期
	for (int i = 0; i < 12; i++) {
		if (w == 5) printf("%d\n", i+1);
		w = (w + monthDays[i]) % 7;
	}
}
