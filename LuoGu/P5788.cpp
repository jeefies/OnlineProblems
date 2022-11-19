#include <iostream>

const int MAXN = 3e6 + 2;

int stk[MAXN], top = 0;
int a[MAXN], ans[MAXN];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	
	for (int i = n; i >= 1; i--) {
		while (top && a[stk[top]] <= a[i]) --top;
		ans[i] = stk[top];
		stk[++top] = i;
	}
	
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	return 0;
}
