#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

struct node {
    int i, lc, rc;
} tree[10];
typedef struct node node;

void preorder(node n) {
    printf("%d ", n.i);

    if (n.lc != -1) preorder(tree[n.lc]);
    if (n.rc != -1) preorder(tree[n.rc]);
}

void inorder(node n) {
    if (n.lc != -1) inorder(tree[n.lc]);
    printf("%d ", n.i);
    if (n.rc != -1) inorder(tree[n.rc]);
}

void postorder(node n) {
    if (n.lc != -1) postorder(tree[n.lc]);
    if (n.rc != -1) postorder(tree[n.rc]);
    printf("%d ", n.i);
}

void levelorder(node n) {
    static node queue[1000];
    int qlen = 0;
    queue[qlen++] = n;

    int i = 0;
    while (i != qlen) {
        if (queue[i].lc != -1) queue[qlen++] = tree[queue[i].lc];
        if (queue[i].rc != -1) queue[qlen++] = tree[queue[i].rc];
        printf("%d ", queue[i++].i);
    }
}

int main(int argc, char * argv[]) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int k; scanf("%d", &k);
        tree[k].i = k;
        scanf("%d%d", &tree[k].lc, &tree[k].rc);
    }

    preorder(tree[1]); putchar('\n');
    inorder(tree[1]); putchar('\n');
    postorder(tree[1]); putchar('\n');
    levelorder(tree[1]); putchar('\n');
	return 0;
}
