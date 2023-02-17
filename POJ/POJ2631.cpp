#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 10000 + 7;

struct Edge {
	int to, next, w;
};

Edge edge[N * 2];
int n;
int head[N], tot = 0;

void add(int u, int v, int w) {
	++tot;
	edge[tot].to = v, edge[tot].next = head[u], edge[tot].w = w, head[u] = tot; 
}

void read() {
	int u, v, w;
	while (~scanf("%d %d %d", &u, &v, &w)) {
		if (u == 0) break;
		add(u, v, w);
		add(v, u, w);
	}
}

bool vis[N];
int diam;
int d1[N], d2[N];
void getDiam(int x) {
	vis[x] = true;
	int y;
	for (int i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (vis[y]) continue;
		getDiam(y); 
		int d = d1[y] + edge[i].w;
		if (d > d1[x]) d2[x] = d1[x], d1[x] = d;
		else if (d > d2[x]) d2[x] = d;
		// printf("d[%d] = {%d, %d}\n", x, d1[x], d2[x]);
	}
	diam = max(diam, d1[x] + d2[x]);
}

int main() {
	read();
	getDiam(1);
	printf("%d", diam);
	return 0;
}
