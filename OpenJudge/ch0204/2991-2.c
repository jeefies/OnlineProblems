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

char num[202] = {0};

int cache[10000] = {0};

int calc() {
	int bits = strlen(num);
	int time = 1;
	int n = 1;
	for (int i = bits - 1; i >= 0; i--) {
		for (int t = 0; t < (num[i] - '0') * time; t++) {
			if (cache[n] == 0) 
				n = cache[n] = (n * 2011) % 10000;
			else 
				n = cache[n];
		}
		time *= 10;
	}

	return n;
}

int main() {
	int n;
	scanf("%d", &n);
	while (n--) {
		scanf("%s", num);
		printf("%d\n", calc());
	}
	return 0;
}
