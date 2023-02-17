#include <stdio.h>

typedef struct __Item {
	int s, v, w;
} Item;

const int N = 1e2 + 7;

int n, v;
Item items[N];

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	scanf("%d %d", &n, &v);
	Item * ptr = items;
	for (int i = 0; i < n; ++i) {
		scanf("%d %d %d", &ptr->v, &ptr->w, &ptr->s);
		++ptr;
	}
	
	ptr = items;
	static int dp[N];
	while (n--) {
		while (ptr->s--) {
			for (int i = v; i >= ptr->v; --i)
				dp[i] = max(dp[i], dp[i - ptr->v] + ptr->w);
		}
		++ptr;
	}
	printf("%d\n", dp[v]);
	return 0;
}