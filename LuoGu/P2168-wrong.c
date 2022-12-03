#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

// 不知道如何处理像示例1的那种情况

typedef char BOOL;
#define TRUE 1
#define FALSE 0

typedef int64_t i64;
i64 min(i64 a, i64 b) {
    return a < b ? a : b;
}

i64 max(i64 a, i64 b) {
    return a > b ? a : b;
}

typedef struct node {
    i64 val;
    i64 dep;
    struct node * childs[10];
} node;

node * newNode(i64 val) {
    node * n = (node *)malloc(sizeof(node));
    memset(n, 0, sizeof(node));
    n->val = val;
    return n;
}

static node * heap[100005];
static i64 tail = 0;

BOOL smaller(node * a, node * b) {
    if (a->val == b->val) return a->dep < b->dep;
    return a->val < b->val;
}

void heap_insert(node * n) {
    heap[++tail] = n;
    node * tmp;

    i64 cur = tail, par = tail >> 1;
    while (par != 0 && smaller(heap[cur], heap[par])) {
        tmp = heap[cur], heap[cur] = heap[par], heap[par] = tmp;
        cur = par, par = par >> 1;
    }
}

void heap_pop() {
    // free(heap[1]);
    heap[1] = heap[tail--];

    node * tmp;
    i64 cur = 1, next = cur << 1;
    while (next <= tail) {
        if (next < tail && smaller(heap[next + 1], heap[next])) ++next;
        if (!smaller(heap[next], heap[cur])) break;
        tmp = heap[cur], heap[cur] = heap[next], heap[next] = tmp;
        cur = next, next = next << 1;
    }
}

node * heap_top() {
    return heap[1];
}

i64 heap_size() {
    return tail;
}

void count_val(node * nd, i64 * len, i64 * maxdep, i64 dep) {
    *maxdep = max(*maxdep, dep);

    BOOL haschild = FALSE;
    for (i64 i = 0; i < 10; i++) {
        if (nd->childs[i] != NULL) {
            haschild = TRUE;
            count_val(nd->childs[i], len, maxdep, dep + 1);
        }
    }

    if (haschild == FALSE) {
        (*len) += dep * nd->val;
    }
}

int main(int argc, char * argv[]) {
    i64 n, k;
    scanf("%lld%lld", &n, &k);
    i64 tmp;
    for (i64 i = 0; i < n; i++) {
        scanf("%lld", &tmp);
        heap_insert(newNode(tmp));
    }

    while ((heap_size() - 1) % (k - 1) != 0) heap_insert(newNode(0));

    while (heap_size() > 1) {
        node * nNode = newNode(0);
        i64 ms = min(heap_size(), k);
        for (i64 i = 0; i < ms; i++) {
            node * top = heap_top();

            nNode->childs[i] = top;
            nNode->val += top->val;
            nNode->dep = max(nNode->dep, nNode->childs[i]->dep + 1);
            heap_pop();
        }
        heap_insert(nNode);
    }

    i64 len = 0, maxdep = 0;
    count_val(heap_top(), &len, &maxdep, 0);
    printf("%lld\n%lld\n", len, maxdep);
    return 0;
}
