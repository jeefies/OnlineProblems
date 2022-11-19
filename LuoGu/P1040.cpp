extern "C" {
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <limits.h>
}

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

int scores[30];

typedef struct tree {
	int index;
	struct tree * lt, * rt;
} tree;

tree * newTreeNode(int i) {
	tree * r = (tree *)malloc(sizeof(tree));
	r->index = i; r->lt = r->rt = NULL;
	return r;
}

tree * build(int l, int r) {
	if (l == r) return NULL;
	if (l + 1 == r) return newTreeNode(l);

	int mins = INT_MAX, mini;
	for (int i = l; i < r; i++) {
		if (scores[i] < mins) {
			mini = i, mins = scores[i];
		}
	}

	tree * root = newTreeNode(mini);
	root->lt = build(l, mini);
	root->rt = build(mini + 1, r);

	return root;
}

int count(tree * r) {
	if (r == NULL) return 1;

	int scr = 1;
	scr *= count(r->lt);
	scr *= count(r->rt);

	if (r->lt == NULL && r->rt == NULL) scr = 0;

	return scr + scores[r->index];
}

void preorder(tree * t) {
	if (t == NULL) return;
	printf("%d ", t->index + 1);
	preorder(t->lt); preorder(t->rt);
}

int main(int argc, char * argv[]) {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", scores + i);
	tree * r = build(0, n);
	printf("%d\n", count(r));
	preorder(r);
	return 0;
}
