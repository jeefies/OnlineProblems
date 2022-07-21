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
	char tmp;
	int count = 0;
	while ((tmp = getchar()) != '\n')
		if ('0' <= tmp && tmp <= '9')
			count++;
	printf("%d\n", count);
}
