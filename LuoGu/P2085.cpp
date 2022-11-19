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

priority_queue <int> q;

void prt() {
	if (!q.empty()) {
		int n = q.top(); q.pop();
		prt();
		printf("%d ", n);
	}
}

int main(int argc, char * argv[]) {
	int n, m;
	scanf("%d%d", &n, &m);

	int a, b, c;
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &a, &b, &c);
		for (int x = 1; x <= m; x++) {
			int y = x * x * a + x * b + c;
			if (q.size() == (size_t)m && y >= q.top()) break;
			q.push(y);
			while (q.size() > (size_t)m) q.pop();
		}
	}

	prt();
	return 0;
}
