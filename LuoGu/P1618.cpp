#include <iostream>
#include <cstring>

int a, b, c;
int tot = 0; 

void av(int i, int j, int k) {
	static bool exi[100];
	for (int l = 0; l < 10; ++l) exi[l] = false;
	int x;
	
	x = i;
	while (x) exi[x % 10] = true, x /= 10;
	x = j;
	while (x) exi[x % 10] = true, x /= 10;
	x = k;
	while (x) exi[x % 10] = true, x /= 10;
	
	if (exi[0]) return;
	bool alle = true;
	for (int l = 1; l < 10; ++l) alle = alle && exi[l];
	if (alle) {
		printf("%d %d %d\n", i, j, k);
		++tot;
	}
}

int main() {
	scanf("%d %d %d", &a, &b, &c);
	
	if (a != 0)
	for (int i = 102; i < 1000; ++i) {
		if (i % a != 0) continue;
		int k = i / a;
		if (k * b >= 1000 || k * c >= 1000) break;
		av(i, k * b, k * c);
	}
	if (!tot) printf("No!!!\n");
	return 0;
}
