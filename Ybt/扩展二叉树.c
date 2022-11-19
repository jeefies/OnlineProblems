#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define LEFT 0
#define RIGHT 1

typedef struct tree {
	char c;
	struct tree * lt, * rt;
} tree;

tree * newTreeNode(char c) {
	tree * r = (tree *)malloc(sizeof(tree));
	r->c = c;
	r->lt = r->rt = NULL;
	return r;
}


void generate(char * s, tree * parent, char status) {
	static int i = 1;
	char c = s[i++];
	if (c == '.' || c == '\0') return;

	tree * newNode = newTreeNode(c);
	if (status == LEFT) parent->lt = newNode;
	else parent->rt = newNode;

	generate(s, newNode, LEFT); generate(s, newNode, RIGHT);
}

void inorder(tree * node) {
	if (node->lt) inorder(node->lt);
	putchar(node->c);
	if (node->rt) inorder(node->rt);
}

void postorder(tree * node) {
	if (node->lt) postorder(node->lt);
	if (node->rt) postorder(node->rt);
	putchar(node->c);
}

int main(int argc, char * argv[]) {
	char s[200];
	scanf("%s", s);
	tree * root = newTreeNode(s[0]);

	generate(s, root, LEFT);
	generate(s, root, RIGHT);

	inorder(root); putchar('\n');
	postorder(root); putchar('\n');

	return 0;
}
