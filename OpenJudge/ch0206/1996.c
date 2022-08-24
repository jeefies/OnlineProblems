#include <stdio.h>

int mts[1002];
int up[1002] = {0};
int down[1002] = {0};

#define max(a,b) (a)>(b)?(a):(b)

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", mts + i);
	}

	for (int i = 1; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (mts[j] < mts[i]) 
				up[i] = max(up[i], up[j] + 1);
		}
	}

	for (int i = N - 2; i > 0; i--) {
		for (int j = N - 1; j > i; j--) {
			if (mts[i] > mts[j])
				down[i] = max(down[i], down[j] + 1);
		}
	}

	int maxn = 0;
	for (int i = 1; i < N; i++) {
		maxn = max(maxn, up[i] + down[i]);
	}

	printf("%d\n", maxn + 1);
}
