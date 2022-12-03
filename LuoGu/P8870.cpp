#include <iostream>
#include <algorithm>

const int N = 2e5 + 50;
int a[N], b[N], t[N];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int rig = std::max(m, n);
	for (int i = 0; i < n; ++i) scanf("%d", a + n - i);
	for (int i = 0; i < m; ++i) scanf("%d", b + m - i);
	
	/*
	printf("A: ");
	for (int i = 1; i <= rig; ++i) printf("%d ", a[i]);
	printf("\nB: ");
	for (int i = 1; i <= rig; ++i) printf("%d ", b[i]);
	putchar('\n');
	*/
	
	for (int i = 1; i <= rig; ++i) {
		t[i] += a[i] + b[i];
		t[i + 1] += t[i] / (i + 1);
		t[i] %= (i + 1);
		// printf("t[%d] to %d, mod %d\n", i, t[i], i + 1);
	}
	
	while (t[rig] > rig) {
		t[rig + 1] += t[rig] / (rig + 1);
		t[rig] %= (rig + 1);
		++rig;
	}
	
	while (rig > 0 && !t[rig]) --rig;
	
	if (rig == 0) printf("0");
	
	while (rig > 0)
		printf("%d ", t[rig--]);
}
