#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

static int bheap[50005], bi = 0, sheap[50005], si = 0;

void binsert(int x) {
	bheap[++bi] = x;

	int tmp;
	int cur = bi, par = bi >> 1;
	// 大的向上走
	while (par != 0 && bheap[cur] > bheap[par]) {
		tmp = bheap[cur], bheap[cur] = bheap[par], bheap[par] = tmp;
		cur = par, par = par >> 1;
	}
}

void bpop() {
	bheap[1] = bheap[bi--];
	int tmp;

	int cur = 1, next = cur << 1;
	while (next <= bi) {
		if (next < bi && bheap[next] < bheap[next + 1]) ++next;
		if (bheap[cur] >= bheap[next]) break;
		tmp = bheap[cur], bheap[cur] = bheap[next], bheap[next] = tmp;
		cur = next, next = cur << 1;
	}
}

void sinsert(int x) {
	sheap[++si] = x;
	int tmp;
	int cur = si, par = si >> 1;
	while (par != 0 && sheap[cur] < sheap[par]) {
		tmp = sheap[cur], sheap[cur] = sheap[par], sheap[par] = tmp;
		cur = par, par >>= 1;
	}
}

void spop() {
	sheap[1] = sheap[si--];
	int tmp;
	int cur = 1, next = cur << 1;
	while (next <= si) {
		if (next < si && sheap[next] > sheap[next + 1]) ++next;
		if (sheap[cur] <= sheap[next]) break;
		tmp = sheap[cur], sheap[cur] = sheap[next], sheap[next] = tmp;
		cur = next, next <<= 1;
	}
}

int btop() {
	return bi == 0 ? 0 : bheap[1];
}

int stop() {
	return si == 0 ? 0 : sheap[1];
}

int main(int argc, char * argv[]) {
	memset(bheap, 0, sizeof(bheap)); memset(sheap, 0, sizeof(sheap));

	int n;
	scanf("%d", &n);

	// int mid = -1;
	for (int i = 0; i < n; i++) {
		int tmp; scanf("%d", &tmp);
		if (tmp <= btop()) binsert(tmp);
		else sinsert(tmp);

		while (si + 1 < bi) {
			sinsert(btop()); bpop();
		}

		while (bi < si) {
			binsert(stop()); spop();
		}

		// printf("BTOP %d, STOP %d\n", btop(), stop());

		if (i % 2 == 0) {
			printf("%d\n", btop());
		}
	}
	return 0;
}
