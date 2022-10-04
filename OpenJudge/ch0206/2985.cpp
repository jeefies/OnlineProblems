#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef int64_t Int;

int main() {
	Int n, target;
	static Int count[1001] = {0};
	static Int nums[20] = {0};

	scanf("%ld%ld", &n, &target);
	for (int i = 0; i < n; i++)
		scanf("%ld", nums + i);

	count[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = target; j >= nums[i]; j--)
			count[j] += count[j - nums[i]];
	}

	printf("%ld\n", count[target]);
}
