#include <stdio.h>


int nums[100001];

void qsort(int fst, int lst) {
	if (fst + 1 >= lst) return;

	int l = fst, r = lst - 1, key = nums[l];

	while (l < r) {
		while (l < r && nums[r] >= key) {
			r--;
		}

		nums[l] = nums[r];

		while (l < r && nums[l] <= key) {
			l++;
		}
		nums[r] = nums[l];
	}
	nums[l] = key;
	// printf("%d %d\n", l, r);
	qsort(fst, l);
	qsort(l + 1, lst);
}

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", nums + i);
	}

	qsort(0, n);

	int k;
	scanf("%d", &k);

	for (int i = n - 1; i > n - 1 - k; i--) {
		printf("%d\n", nums[i]);
	}
}
