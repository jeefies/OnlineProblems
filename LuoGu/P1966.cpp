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
		// �����һ����Ϊ��ɢ����ò�Ҫ��0��ʼ���� 
		B[i] = make_pair(tmp, i + 1);
	}
	
	// �������������еĴ�С����
	// ͼ����û����д���򣬴�������������ַ��� 
	sort(A, A + n, cmp);
	sort(B, B + n, cmp);
	
	long long r = 0;
	for (int i = 0; i < n; i++) {
		// �����ǰ�A�����е�i�������B�����е�i��������
		// ����C[i]����������������A[i]������ĵ��� 
		C[A[i].second] = B[i].second;
	}

	// ��״����������Եľ���˼·���Բο�������д�Ĳ���
	// ƪ��ԭ��(��Ҫ���Һ���)����û�����	
	for (int i = n - 1; i >= 0; i--) {
		r = (r + getsum(C[i] - 1)) % 99999997;
		update(C[i], 1);
	}
	printf("%ld\n", r);
}
