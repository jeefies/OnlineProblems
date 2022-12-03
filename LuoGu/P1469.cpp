#include <cstdio>

int main() {
	int n;
	scanf("%d", &n);
	int x = 0, t;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &t);
		x ^= t;
	}
	printf("%d", x);
}
