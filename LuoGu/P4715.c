#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
	int index, abi;
} team;

team allt[1 << 7];

int main(int argc, char * argv[]) {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &(allt[i].abi));
		allt[i].index = i;
	}

	for (int k = 0; k < (n - 1); k++) {
		for (int i = 0; i < (1 << (n - k - 1)); i++)
			if (allt[i * 2].abi < allt[i * 2 + 1].abi) {
				allt[i] = allt[i * 2 + 1];
			} else {
				allt[i] = allt[i * 2];
			}
	}

	if (allt[0].abi < allt[1].abi) {
		printf("%d\n", allt[0].index + 1);
	} else {
		printf("%d\n", allt[1].index + 1);
	}
	return 0;
}
