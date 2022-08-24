#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nums[200000] = {0};

int main() {
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", nums + i);
	}
	
	long long sum = 0, maxn = -100000;
	for (int i = 0; i < n; i++) {
		sum += nums[i];
		if (sum > maxn) maxn = sum;
		if (sum < 0) sum = 0;
	}
	
	printf("%ld\n", maxn);
	return 0;
}
