#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int N = 5e4;

int head[N], size = 0;
struct Edge {
	int to, next, w;
} edge[N];

void add(int u, int v, int w) {
	++size;
	edge[size] = {v, head[u], w};
	head[u] = size;
}

int n;

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
					if (++it[t] > n) return false;
				}
			}
		}
	}
	return true;
}

int main() {
	int m;
	scanf("%d %d", &n, &m);
	
	int k, a, b, c;
	// k == 1: n[a] - n[b] >= c => n[b] - n[a] <= -c
	// k == 2: n[a] - n[b] <= c
	// k == 3: n[a] - n[b] <= 0 && n[b] - n[a] <= 0
	for (int i = 0; i < m; ++i) {
		scanf("%d", &k);
		if (k == 1) {
			scanf("%d %d %d", &a, &b, &c);
			add(a, b, -c);
		} else if (k == 2) {
			scanf("%d %d %d", &a, &b, &c);
			add(b, a, c);
		} else {
			scanf("%d %d", &a, &b);
			add(a, b, 0); add(b, a, 0);
		}
	}
	
	for (int i = 1; i <= n; i++) add(0, i, 0);
	
	// printf("Graph set!\n");
	
	static int dis[N]; memset(dis, 0x7F, sizeof(dis));
	if (spfa(0, dis)) printf("Yes");
	else printf("No");
	return 0;
}
