#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e7 + 7;

char a[N], b[N];
int kmp[N];

int main() {
	scanf("%s", b + 1);
	scanf("%s", a + 1);
	
	// use a to match b
	register int alen = strlen(a + 1), blen = strlen(b + 1);
	
	kmp[1] = 0;
	// 寻找a的kmp数组
	for (register int i = 2, j = 0; i <= alen; ++i) {
		while (j && a[j + 1] != a[i]) j = kmp[j];
		if (a[i] == a[j + 1]) ++j;
		kmp[i] = j;
	}
	
	// 与b匹配 
	for (register int i = 1, j = 0; i <= blen; ++i) {
		while (j && (b[i] != a[j + 1])) j = kmp[j];
		if (b[i] == a[j + 1]) ++j;
		if (j == alen) {
			printf("%d\n", i - alen + 1);
			j = kmp[j];
		}
	}
	
	for (register int i = 1; i <= alen; ++i) {
		printf("%d ", kmp[i]);
	}
	return 0;
} 