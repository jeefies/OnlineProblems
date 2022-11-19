#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

struct tree {
	char c;
	struct tree * lt, * rt;
};
typedef struct tree tree;

tree * newTreeNode(char c) {
	tree * t = (tree *)malloc(sizeof(tree));
	t->c = c;
	t->lt = t->rt = NULL;
	return t;
}

tree * leafs[1 << 10];

void postorder(tree * node) {
	if (node->lt) postorder(node->lt);
	if (node->rt) postorder(node->rt);
	putchar(node->c);
}

int main(int argc, char * argv[]) {
	int n;
	scanf("%d", &n); while (getchar() != '\n');
	int maxLeaf = pow(2, n);
	for (int i = 0; i < maxLeaf; i++) {
		char tmp = getchar();
		leafs[i] = newTreeNode(tmp == '1' ? 'I' : 'B');
	}

	for (int i = n; i >= 0; i--) {
		maxLeaf = pow(2, i - 1);
		for (int k = 0; k < maxLeaf; k++) {
			tree * lt = leafs[k * 2], * rt = leafs[k * 2 + 1];
			tree * newNode = newTreeNode(lt->c == rt->c ? lt->c : 'F');
			newNode->lt = lt, newNode->rt = rt;
			leafs[k] = newNode;
		}
	}

	postorder(leafs[0]);
	return 0;
}
