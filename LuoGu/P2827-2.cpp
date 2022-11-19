#include <queue>
#include <iostream>

using namespace std;
typedef unsigned long long ull;

int n, m, q, u, v, t;
double p;

void prt(priority_queue<int> & que, int depth, int offset) {
	putchar('\n');
	while (!que.empty()) {
		if (depth++ % t == 0) printf("%d ", que.top() + offset);
		que.pop();
	} 
}

signed main() {
	cin >> n >> m >> q >> u >> v >> t;
	p = (double)u / (double)v;
	
	priority_queue<int> pq;
	int ai;
	for (int i = 0; i < n; i++) {
		scanf("%d", &ai);
		pq.push(ai);
	}
	
	int offset = 0;
	for (int i = 1; i <= m; i++) {
		int top = pq.top() + offset; pq.pop();
		if (i % t == 0) printf("%d ", top);
		int px = (int)(p * top); // printf("Px = %d, push in %d, %d\n", px, px - offset, top - px + offset);
		pq.push(px - offset - q); pq.push(top - px - offset - q);
		
		offset += q;
	}
	
	prt(pq, 1, offset);
	return 0;
}
