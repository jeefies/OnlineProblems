#include <iostream>
#include <queue>
#include <stack>
#include <cstring>
#include <climits> 

using namespace std;

const int N = 5e4 + 2, INF = 0x7F7F7F7F;

struct Edge {
	int to, next, w;
};
int head[N], size = 0;
Edge edge[N];
int n, m;

void add(int u, int v, int w) {
	++size;
	edge[size].next = head[u], head[u] = size;
	edge[size].to = v, edge[size].w = w;
}

// cprt: comparative
inline static bool spfa(int s, int * cprt) {
	static int in[N] = {0}; // memset(in, 0, sizeof(in));
	static int it[N] = {0}; // memset(it, 0, sizeof(it));
	
	queue<int> que;
	cprt[s] = 0; que.push(s);
	
	while (que.size()) {
		int top = que.front(); que.pop();
		in[top] = 0;
		
		
		for (int i = head[top]; i; i = edge[i].next) {
			int to = edge[i].to, w = edge[i].w;
			if (cprt[to] > w + cprt[top]) {
				cprt[to] = w + cprt[top];
				if (!in[to]) {
					que.push(to), in[to] = true;
					if (++it[to] > n) return false;
				}
			}
		}
	}
	
	return true;
}

int main() {
	scanf("%d %d", &n, &m);
	
	// establish a strong connect source point
	for (int i = 1; i <= n; i++) {
		add(0, i, 0);
	}
	
	int a, b, k;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &k);
		add(b, a, k); // we need to build a reversed map 
	}
	
	static int cprt[N]; memset(cprt, 0x7F, sizeof(cprt));
	if (spfa(0, cprt)) {
		for (int i = 1; i <= n; i++) printf("%d ", cprt[i]);
	} else
		printf("NO\n");
		
	return 0;
}
