#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

struct tree {
	char c;
	int cds;
	struct tree * lt, * rt;
};
typedef struct tree tree;

tree * newTreeNode(char c) {
	tree * t = (tree *)malloc(sizeof(tree));
	t->c = c;
	t->cds = 0, t->lt = t->rt = NULL;
	return t;
}

tree * generateTree(char * prod, char * inod, int pl, int pr, int il, int ir) {
	if (pl >= pr) return NULL;
	tree * root = newTreeNode(prod[pl]);
	if (pl + 1 == pr) return root;

	int mid;
	for (mid = 0; il + mid < ir; mid++) {
		if (prod[pl] == inod[il + mid]) break;
	}

	root->lt = generateTree(prod, inod, pl + 1, pl + 1 + mid, il, il + mid);
	root->rt = generateTree(prod, inod, pl + mid + 1, pr, il + mid + 1, ir);
	return root;
}

int count_child(tree * node) {
	int c = 0;
	if (node->lt) c += count_child(node->lt);
	if (node->rt) c += count_child(node->rt);
	return (node->cds = (c == 0 ? 1 : c));
}

void output(tree * node) {
	for (int i = 0; i < node->cds; i++) putchar(node->c);
	putchar('\n');
	if (node->lt) output(node->lt);
	if (node->rt) output(node->rt);
}

int main(int argc, char * argv[]) {
	char prod[200] = {0}, inod[200] = {0};
	scanf("%s\n%s", prod, inod);
	tree * root = generateTree(prod, inod, 0, strlen(prod), 0, strlen(inod));

	count_child(root);
	output(root);
	return 0;
}
