#include <stdio.h>
#include <string.h>

char num[202] = {0};

int cache[202] = {0};

int calc() {
	int bits = strlen(num);
	int time = 1;
	int n = 1;
	for (int i = bits - 1; i >= 0; i--) {
		for (int t = 0; t < num[i] - '0'; t++) {
			n = n * cache[time] % 10000;
		}
		time++;
	}

	return n;
}

int main() {
	int n;
	scanf("%d", &n);
	cache[1] = 2011;
	
	for (int i = 2; i < 202; i++) {
		cache[i] = 1;
		for (int t = 0; t < 10; t++) cache[i] = cache[i] * cache[i - 1] % 10000;
	}

	while (n--) {
		scanf("%s", num);
		printf("%d\n", calc());
	}
	return 0;
}
