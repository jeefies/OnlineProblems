#include <cstdio>
#include <cstring>
#include <cmath>

typedef long long Int;

Int g_r[500] = {0};
#define numByte sizeof(Int)*500

void multi(Int * r, int x) {
	Int tmp[501] = {0};
	
	for (int i = 0; i < 500; i++) {
		tmp[i] += r[i] * x;
		tmp[i + 1] += tmp[i] / 10;
		tmp[i] %= 10;
	}
	
	memcpy(r, tmp, numByte);
}

void printLargeNum(Int * n) {
	int cnt = 0;
	for (int i = 500 - 1; i >= 0; i--) {
		putchar(n[i] + '0');
		if (++cnt % 50 == 0) putchar('\n');
	}
}

int main() {
	int p = 3021377;
	scanf("%d", &p);
	int width = ceil(p * log10(2));
	printf("%d\n", width);
	
	++g_r[0];
	while (p >= 30) {
		multi(g_r, 1 << 30);
		p -= 30;
	}
	
	while (p >= 10) {
		multi(g_r, 1 << 10);
		p -= 10;
	}
	
	while (p >= 4) {
		multi(g_r, 1 << 4);
		p -= 4;
	}
	
	while (p >= 1) {
		multi(g_r, 2);
		p -= 1;
	}
	
	--g_r[0];
	printLargeNum(g_r);
}
