#warning 这是使用了空间压缩算法的版本

#include <stdio.h>
#include <string.h>

int area[100];

#define min(a,b) (a<b?a:b)

int main() {
	int n;
	scanf("%d", &n);

	memset(area, 0x7F, sizeof(area));

	int tmp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &tmp);
			if (i == 0) area[j] = tmp + (j > 0 ? area[j - 1] : 0);
			else if (j == 0) area[j] += tmp;
			else area[j] = tmp + min(area[j - 1], area[j]);
		}
	}

	printf("%d\n", area[n - 1]);
	return 0;
}
