#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

int fastread() {
	char tmp;
	int r = 0;
	while (!isdigit((tmp = getchar())));
	do {
		r = r * 10 + tmp - '0';
	} while (isdigit(tmp = getchar()));
	return r;
}

int nums[500002] = {0};
long long cnt = 0;

int * mergeSort(int * num, int start, int end) {
	int mid = (start + end) / 2;
	int * rn = (int *)malloc(sizeof(int) * (end - start));
	
	if (start + 1 == end) {
		*rn = num[start];
		return rn;
	}
	
	int * left = mergeSort(num, start, mid);
	int ll = mid - start;
	int * right = mergeSort(num, mid, end);
	int rl = end - mid;
	
	int l = 0, r = 0, k = 0;
	while (l < ll && r < rl) {
		if (left[l] <= right[r]) rn[k++] = left[l++];
		else cnt += ll - l, rn[k++] = right[r++];
	}
	
	while (l < ll) rn[k++] = left[l++];
	while (r < rl) rn[k++] = right[r++];
	
	free(left); free(right);
	
	assert(k == end - start);
	return rn;
} 

int main() {
	int n = fastread();
	for (int i = 0; i < n; i++) {
		nums[i] = fastread();
	}
	
	// ×ó±ÕÓÒ¿ª 
	int * sorted = mergeSort(nums, 0, n);
	
	free(sorted);
	printf("%ld\n", cnt);
	return 0;
	
}
