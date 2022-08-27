#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include <algorithm>
#include <iostream>

using namespace std;

#define MAXN 100005
typedef struct num {
	int v, i;
} num; 

num A[MAXN], B[MAXN];
int C[MAXN];

long long cnt = 0;

// 这里用了动态分配的内存
// 这年头不会还有人看不懂归并排序吧（手动狗头） 
int * mergeSort(int * v, int left, int right) {
	int * ret = (int *)malloc(sizeof(int) * (right - left));
	if (left + 1 == right) {
		ret[0] = v[left];
		return ret;
	}
	
	int mid = (left + right) / 2;
	
	int * l = mergeSort(v, left, mid);
	long long li = 0, le = mid - left;
	int * r = mergeSort(v, mid, right);
	long long ri = 0, re = right - mid;
	
	int i = 0;
	while (li < le && ri < re) {
		if (l[li] <= r[ri]) ret[i++] = l[li++];
		else cnt += le - li, ret[i++] = r[ri++];
	}
	
	while (li < le) ret[i++] = l[li++];
	while (ri < re) ret[i++] = r[ri++];
	
	free(l); free(r);
	
	assert(i == right - left);
	return ret;
}

bool cmp(num & i, num & j) {
	return i.v < j.v;
}

int main() {
	int n; scanf("%d", &n);
	
	int tmp;
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i].v);
		A[i].i = i;
	}
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &B[i].v);
		B[i].i = i;
	}
	
	sort(A, A + n, cmp);
	sort(B, B + n, cmp);

	for (int i = 0; i < n; i++) {
		C[A[i].i] = B[i].i;
	}

	int * needFree = mergeSort(C, 0, n);
	free(needFree);
	
	cout << cnt % long(1e8 - 3) << endl;
}
