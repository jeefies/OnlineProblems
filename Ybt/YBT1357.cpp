#include <iostream>
#include <stack>
#include <string>

using namespace std;

const int fuck = 1000;
int order[fuck];

void rev(int x, int y) {
	int tmp;
	while (x < y) {
		tmp = order[x], order[x] = order[y], order[y] = tmp;
		++x, --y;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", order + i);
	}
	
	int k, needrev = 0;
	for (int i = 0; i < n - 1; i++) {
		if (order[i] < order[i + 1] && !needrev) k = i, needrev = 1;
		else if (needrev && order[i] > order[i + 1]) rev(k, i), needrev = 0;
	}
	
	if (needrev) {
		printf("NO\n");
		return 0;
	}
	
	for (int i = 0; i < n - 1; i++) {
		if (order[i] < order[i + 1]) {
			printf("NO\n"); return 0;
		}
	}
	
	printf("YES\n");
	return 0;
}
