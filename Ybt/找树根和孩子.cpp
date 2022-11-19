#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

int main(int argc, char * argv[]) {
	int n, m;
	scanf("%d%d", &n, &m);

	int prt[1000] = {0};
	int childs[1000] = {0};
	for (int i = 0; i < m; i++) {
		int p, c;
		scanf("%d%d", &p, &c);
		c[prt] = p;
		p[childs] ++;
	}

	int root, maxi, maxc = 0;
	for (int i = 1; i <= n; i++) {
		if (prt[i] == 0) {
			root = i;
		}

		if (childs[i] > maxc) {
			maxi = i, maxc = childs[i];
		}
	}

	printf("%d\n%d\n", root, maxi);

	for (int i = 1; i <= n; i++) {
		if (i[prt] == maxi) {
			printf("%d ", i);
		}
	}
	return 0;
}
