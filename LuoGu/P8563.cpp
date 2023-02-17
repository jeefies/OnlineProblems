extern "C" {
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <limits.h>
}

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

int n, q;
int a[200002];

const long long MAXN = (1ll << 30);

void maxMul(int l, int r) {
	// printf("Mul [%d, %d]\n", l, r);

	if (r - l >= 62) {
		printf("Too large\n");
		return;
	}

	int ln = 0, rn, nc = 0;
	for (int i = l; i <= r; ++i) {
		if (a[i] < 0) {
			++nc, rn = i;
			if (!ln) ln = i;
		}
	}

	long long ans = 1;
	if (nc % 2 == 0) {
		if (r - l > 30) {
			printf("Too large\n");
			return;
		}
		for (int i = l; i <= r; ++i) {
			if ((ans *= abs(a[i])) > MAXN) {
				printf("Too large\n");
				return;
			}
		}
	} else {
		long long lans = 1, rans = 1;
		for (int i = l; i < rn; ++i) {
			if ((lans *= a[i]) > MAXN || lans < -MAXN) {
				printf("Too large\n");
				return;
			}
		}
		for (int i = ln + 1; i <= r; ++i) {
			if ((rans *= a[i]) > MAXN || rans < -MAXN) {
				printf("Too large\n");
				return;
			}
		}
		ans = max(lans, rans);
	}
	printf("%lld\n", ans);	
	return;
}

int main(int argc, char * argv[]) {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	while (q--) {
		int op;
		int i, k;
		scanf("%d%d%d", &op, &i, &k);
		switch (op) {
			case 1:
				a[i] = k;
				break;
			case 2:
				maxMul(i, k);
		}
	}
	return 0;
}
