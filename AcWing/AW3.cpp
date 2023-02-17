#include <stdio.h>
#include <string.h>

const int N = 1e3 + 7;

int n, v;
struct Item {
	int v, w;
};
typedef struct Item Item;

inline int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	scanf("%d %d", &n, &v);
	static Item items[N];
	Item * ptr = items;
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &ptr->v, &ptr->w);
		++ptr;
	}
	
	static int dp[N] = {0};
	ptr = items;
	while (n--) {
		for (int i = ptr->v; i <= v; ++i) {
			dp[i] = max(dp[i], dp[i - ptr->v] + ptr->w);
		}
		++ptr;
	}
	
	printf("%d\n", dp[v]);
	return 0;
}