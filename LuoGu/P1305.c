#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define hx(c) (c=='*' ? 0 : c)
#define rhx(c) c
// #define hx(c) (c=='*' ? 0 : (c-'a'+1))
// #define rhx(c) (c + 'a' - 1)

char parent[128];
char childs[128][2];

void preorder(int i) {
	printf("%c", rhx(i));
	if (childs[i][0]) preorder(childs[i][0]);
	if (childs[i][1]) preorder(childs[i][1]);
}

int main(int argc, char * argv[]) {
	memset(childs, 0, sizeof(childs));

	int n;
	scanf("%d", &n);

	char root = 0;
	char pa, lt, rt;
	for (int i = 0; i < n; i++) {
		scanf("\n%c%c%c", &pa, &lt, &rt);
		if (root == 0) root = pa;

		childs[hx(pa)][0] = hx(lt);
		childs[hx(pa)][1] = hx(rt);
	}

	preorder(root);
	return 0;
}
