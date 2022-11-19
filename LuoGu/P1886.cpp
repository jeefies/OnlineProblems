#include <iostream>

const int N = 2e6 + 2;

int n, k;
int a[N], que[N], head = 0, tail = -1;

signed main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	
	head = 0, tail = -1;
	for (int i = 0; i < n; i++) {
		while (head <= tail && que[head] <= i - k) ++head;
		while (head <= tail && a[que[tail]] >= a[i]) --tail;
		que[++tail] = i;
		if (i + 1 >= k) std::cout << a[que[head]] << ' ';
	}
	std::cout << '\n';
	
	head = 0, tail = -1;
	for (int i = 0; i < n; i++) {
		while (head <= tail && que[head] <= i - k) ++head;
		while (head <= tail && a[que[tail]] <= a[i]) --tail;
		que[++tail] = i;
		if (i + 1 >= k) std::cout << a[que[head]] << ' ';
	}
	std::cout << '\n';

	return 0;
}
