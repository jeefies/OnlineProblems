#include <stdio.h>

int his[10001] = {0};

int main() {
	int n, b;
	scanf("%d%d", &n, &b);

	while (n--) {
		int tmp;
		scanf("%d", &tmp);
		his[tmp]++;
	}

	int c = 0;
	for (int i = 10000;i > 0; i--) {
		if (b <= 0) break;
		if (his[i] > 0) {
			b -= i;
			c++;
			his[i++]--;
		}
	}

	printf("%d\n", c);
}
