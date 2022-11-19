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

static priority_queue<int> q; // ´ó¸ù¶Ñ
static int A[100000], B[100000];

void prt() {
	if (!q.empty()) {
		int k = q.top(); q.pop();
		prt();
		printf("%d ", k);
	}
}

int main(int argc, char * argv[]) {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", A + i);
	}

	for (int i = 0; i < n; i++) {
		scanf("%d", B + i);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			q.push(A[i] + B[j]);
			while (q.size() > (size_t)n) q.pop();
			if (q.size() == (size_t)n && q.top() <= A[i] + B[j]) break;
		}
	}

	prt();
	return 0;
}
