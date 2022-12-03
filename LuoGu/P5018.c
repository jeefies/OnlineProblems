#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef int16_t i16;
typedef int64_t i64;

#define OFFSET 3

int n;
i16 nums[1 << 20] = {0};
int tree[2 << 20] = {0};
int node[1 << 20] = {0};

int max(int a, int b) {
	return a > b ? a : b;
}


int countNodes(int i) {
	if (node[i] != 0) return node[i];

	int lt = tree[i * 2 - 1], rt = tree[i * 2];
	int c = 1;
	if (lt != -1) c += countNodes(lt);
	if (rt != -1) c += countNodes(rt);
	return node[i] = c;
}

int thesame(int x, int y) {
	if (x == -1 && y == -1) return 1;
	if (x == -1 || y == -1) return 0;
	if (nums[x] != nums[y]) return 0;
	return thesame(tree[x * 2], tree[y * 2 - 1]) && thesame(tree[x * 2 - 1], tree[y * 2]);
}

int maxNodes = 1;
void search_max(int i) {
	int lt = tree[i * 2 - 1], rt = tree[i * 2];
	if (thesame(lt, rt)) {
		maxNodes = max(maxNodes, countNodes(i));
	}
}

int main(int argc, char * argv[]) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%hd", nums + i);
	}

	for (int i = 1; i <= n; i++) {
		scanf("%d%d", tree + i * 2 - 1, tree + i * 2);
		// revt[i * 2] = tree[i * 2 - 1], revt[i * 2 - 1] = tree[i * 2];
	}

	for (int i = 1; i <= n; i++) {
		search_max(i);
	}

	printf("%d", maxNodes);

	return 0;
}
