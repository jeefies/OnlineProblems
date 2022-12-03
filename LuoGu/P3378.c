#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define MAXSIZE 1000006

// 利用二叉堆的实现方法

static int heap[MAXSIZE], tail = 0;

void heap_insert(int x) {
	heap[++tail] = x;
	int tmp;
	int cur = tail, par = cur >> 1;
	while (par != 0 && heap[par] > heap[cur]) {
		tmp = heap[cur], heap[cur] = heap[par], heap[par] = tmp;
		cur = par, par = par >> 1;
	}
}

int heap_top() {
	return tail == 0 ? 0 : heap[1];
}

void heap_pop() {
	int tmp;
	// tmp = heap[tail--], heap[tail] = heap[1], heap[1] = tmp;
	heap[1] = heap[tail--];
	int cur = 1, next = cur << 1;
	while (next <= tail) {
		// 子节点取最小的一边
		if (next < tail && heap[next] > heap[next + 1]) next += 1;
		// 符合树的结构
		if (heap[cur] <= heap[next]) break;
		tmp = heap[cur], heap[cur] = heap[next], heap[next] = tmp;
		cur = next, next = (next << 1);
	}
}

int main(int argc, char * argv[]) {
	int n;
	scanf("%d", &n);

	int op;
	for (int i = 0; i < n; i++) {
		scanf("%d", &op);
		if (op == 1) {
			int x;
			scanf("%d", &x);
			heap_insert(x);
		} else if (op == 2) {
			printf("%d\n", heap_top());
		} else {
			heap_pop();
		}
	}
	return 0;
}
