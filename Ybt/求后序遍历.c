#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

struct tree {
	char c;
	struct tree * lt,  * rt;
};
typedef struct tree tree;

tree * newTreeNode(char c) {
	tree * r = (tree *)malloc(sizeof(tree));
	memset(r, 0, sizeof(tree));
	r->c = c;
	return r;
}

tree * generate(char * ps, char * is, int pl, int pr, int il, int ir) {
	tree * root = newTreeNode(ps[pl]);

	if (pl >= pr) return NULL;
	if (pl + 1 == pr) return root;

	int mid = 0;
	for (mid = 0; il + mid < ir; mid++) {
		if (ps[pl] == is[il + mid]) break;
	}

	tree * left = generate(ps, is, pl + 1, pl + 1 + mid, il, il + mid);
	tree * right = generate(ps, is, pl + 1 + mid, pr, il + mid + 1, ir);

	root->lt = left, root->rt = right;
	return root;
}

void postorder(tree * node) {
	if (node->lt) postorder(node->lt);
	if (node->rt) postorder(node->rt);
	putchar(node->c);
}

int main(int argc, char * argv[]) {
	char inod[100] = {0}, preod[100] = {0};
	scanf("%s\n%s", preod, inod);
	// printf("Get preod, inod: %s %s\n", preod, inod);
	tree * root = generate(preod, inod, 0, strlen(preod), 0, strlen(preod));
	postorder(root);
	return 0;
}
