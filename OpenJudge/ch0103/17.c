
/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0103/17/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <math.h>

float distance(int a, int b, int m, int n) {
	float dx = a - m, dy = b - n;
	return sqrt(dx * dx + dy * dy);
}

int main() {
	float a, b, m, n, x, y;
	scanf("%f%f%f%f%f%f", &a, &b, &m, &n, &x, &y);
	float l1 = distance(a, b, m, n);
	float l2 = distance(a, b, x, y);
	float l3 = distance(m, n, x, y);
	float p = (l1 + l2 + l3) / 2;
	printf("%.2f", sqrt(p * (p - l1) * (p - l2) * (p - l3)));
	return 0;
}
