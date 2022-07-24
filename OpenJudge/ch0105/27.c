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
#include <unistd.h>

int main() {
	int aim;
	scanf("%d",&aim);

	double i = 0;
	double n = 0;
	while (n <= aim) {
		n += 1 / ++i;
	}

	printf("%.0lf\n", i);
}
