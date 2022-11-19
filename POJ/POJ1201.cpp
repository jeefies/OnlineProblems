#include <iostream>
#include <cstring>
#include <queue>
#include <climits>

using namespace std;

const int N = 5e5;

int head[N], size = 0;
struct Edge {
	int to, w, next;
} edge[N];

void add(int u, int v, int w) { ++size;
	edge[size].next = head[u], head[u] = size;
	edge[size].to = v, edge[size].w = w;
}

int n, mb = 0, ma = INT_MAX;

bool spfa(int s, int * num) {
	static int inq[N]; // memset(in, 0, sizeof(in));
	static int it[N]; // memset(it, 0, sizeof(it));
	
	queue<int> que; que.push(s);
	num[s] = 0;
	
	while (que.size()) {
		int p = que.front(); que.pop();
		inq[p] = false;
		
		for (int i = head[p]; i; i = edge[i].next) {
			int t = edge[i].to, w = edge[i].w;
			if (num[t] > num[p] + w) {
				num[t] = num[p] + w;
				if (!inq[t]) {
					inq[t] = true; que.push(t);
					if (++it[t] > mb) return false;
				}
			}
		}
	}
	return true;
}

int main() {
	scanf("%d", &n);
	
	// n[b] - n[a - 1] >= k
	// => n[a - 1] - n[b] <= -k
	// => add(b, a - 1, -k)
	// => add(b + 1, a, -k) // for we need to avoid `a < 0`
	int a, b, k;
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &a, &b, &k);
		mb = max(mb, b + 1); // the boundary, b is always greater than a
		ma = min(ma, a);
		add(b + 1, a, -k); // origin should be `add(a-1, b, k)`, so we tranform it right to avoid `a == -1`.
	}

	// !! 0 <= n[k] - n[k-1] <= 1
	// => n[k-1] - n[k] <= 0 && n[k] - n[k-1] <= 1
	for (int a = ma; a < mb; a++) {
		add(a + 1, a, 0); add(a, a + 1, 1);
	}
	
	static int num[N]; memset(num, 0x7F, sizeof(num));
	if (!spfa(mb, num)) {
		printf("Fuck you!\n");
		return 0;
	};
	// for (int i = 1; i <= mb; i++) printf("%d ", num[i]); putchar('\n');
	printf("%d ", -num[ma]);
}
