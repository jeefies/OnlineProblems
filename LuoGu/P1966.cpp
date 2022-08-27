#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

#define MAXN 100005
pair<int, int> A[MAXN], B[MAXN];
int C[MAXN] = {0};
int BIT[MAXN] = {0};
int lowbit(int i) {
	return i & -i;
}

void update(int i, int k) {
	while (i < MAXN) {
		BIT[i] += k;
		i += lowbit(i);
	}
}

int getsum(int i) {
	int r = 0;
	while (i > 0) {
		r += BIT[i];
		i -= lowbit(i);
	}
	return r;
}

bool cmp(pair<int, int> & a, pair<int, int> & b) {
	return a.first < b.first;
}

int main() {
	int n; scanf("%d", &n);
	
	int tmp;
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		A[i] = make_pair(tmp, i);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		// 这里加一是因为离散化最好不要从0开始记起 
		B[i] = make_pair(tmp, i + 1);
	}
	
	// 按照数在序列中的大小排序
	// 图方便没有手写排序，打包，就用了这种方法 
	sort(A, A + n, cmp);
	sort(B, B + n, cmp);
	
	long long r = 0;
	for (int i = 0; i < n; i++) {
		// 这里是把A数组中第i大的数与B数组中第i大的数配对
		// 但是C[i]所代表的数还是最初A[i]所代表的的数 
		C[A[i].second] = B[i].second;
	}

	// 树状数组求逆序对的具体思路可以参考其他人写的博客
	// 篇幅原因(主要是我很懒)所以没有详解	
	for (int i = n - 1; i >= 0; i--) {
		r = (r + getsum(C[i] - 1)) % 99999997;
		update(C[i], 1);
	}
	printf("%ld\n", r);
}
