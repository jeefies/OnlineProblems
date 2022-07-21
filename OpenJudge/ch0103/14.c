/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/14/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <math.h>

int main() {
	int h, r;
	scanf("%d%d", &h, &r);
	double oneBucket = r * r * 3.14159 * h;
	double needBuckets = 20000 / oneBucket;
	int lessBuckets = (int)needBuckets;
	if ((double)lessBuckets != needBuckets) {
		lessBuckets++;
	}
	printf("%d\n", lessBuckets);
	return 0;
}
