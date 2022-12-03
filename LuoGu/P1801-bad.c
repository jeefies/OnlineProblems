#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#warning 这是正确的，但是会超时

int nums[200000];
int getp[200000];

typedef struct tree {
    int lc, rc, val;
    struct tree *lt, *rt;
} tree;
tree * root = NULL;

tree * newTreeNode(int val) {
    tree * t = (tree *)malloc(sizeof(tree));
    t->val = val, t->lc = t->rc = 0, t->lt = t->rt = NULL;
    return t;
}

void bst_insert(int x) {
    if (root == NULL) {
        root = newTreeNode(x);
        return;
    }

    tree * node = root;
    while (1) {
        if (x < node->val) {
            if (node->lt == NULL) {
                node->lt = newTreeNode(x);
                return;
            }
            node->lc++;
            node = node->lt;
        } else {
            if (node->rt == NULL) {
                node->rt = newTreeNode(x);
                return;
            }
            node->rc++;
            node = node->rt;
        }
    }
}

int getKinorder(tree * node, int * k) {
    if (*k < 0) return 0;
    int v = 0;
    if (node->lt) v += getKinorder(node->lt, k);
    if (--(*k) == 0) return node->val;
    if (node->rt) v += getKinorder(node->rt, k);
    return v;
}

int bst_getKth(int kth) {
    int k = kth;
    return getKinorder(root, &k);
}

int main(int argc, char * argv[]) {
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++) scanf("%d", nums + i);
    for (int i = 0; i < n; i++) scanf("%d", getp + i);

    int ri = 0, ni = 0, kth = 0;
    for (ri = 0; ri < n; ri++) {
        ++kth;
        for (;ni < getp[ri]; ni++) {
            bst_insert(nums[ni]);
        }

        printf("%d\n", bst_getKth(kth));
    }
	return 0;
}
