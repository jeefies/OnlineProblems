#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

typedef char BOOL;

struct tree {
    BOOL isend;
    struct tree * childs[26];
};
typedef struct tree tree;

tree * newTreeNode(char isend) {
    tree * r = (tree *)malloc(sizeof(tree));
    memset(r, 0, sizeof(tree)); // FUCKING MEMORY ALLOCATION
    r->isend = isend;
    return r;
}

tree * root;

void insert(char * s) {
    int l = strlen(s), i = 0;
    tree * node = root;
    for (i = 0; i < l; i++) {
        int ci = s[i] - 'A';
        if (node->childs[ci] == NULL) {
            node->childs[ci] = newTreeNode(i + 1 == l ? TRUE : FALSE);
        }
        node = node->childs[ci];
    }
}

int cnt(tree * node) {
    int total = 0;
    for (int i = 0; i < 26; i++) {
        if (node->childs[i] != NULL)
            total += cnt(node->childs[i]);
    }
    return total + 1;
}

void read(char * s) {
    char tmp = getchar();
    int i = 0;
    while (tmp != EOF && tmp != '\n') {
        s[i++] = tmp; tmp = getchar();
    }
    // printf("Readline %s\n", s);
}

int main() {
    // INIT
    root = newTreeNode(FALSE);

    // read and process
    char word[63];
    while (TRUE) {
        // clear previous data
        memset(word, 0, sizeof(word));
        // read(word);
        // if (word[0] == 0) break;
        if (scanf("%s\n", word) == -1) break;
        insert(word);
    }

    // output answer
    printf("%d\n", cnt(root));
	return 0;
}
