#include <iostream>

using namespace std;

const int N = 100;

struct Edge {
	int to, next;
};

Edge edge[N];
int head[N], tot = 0, n;

void add(int u, int v) {
	++tot;
	edge[tot] = {v, head[u]}, head[u] = tot;
}

int root = 1, core = 0;
int siz[N], par[N];
void getCore(int x) {
	siz[x] = 1;
	for (int i = head[x]; i; i = edge[i].next) {
		int y = edge[i].to; 
		if (par[x] != y) {
			par[y] = x;
			getCore(y);
			siz[x] += siz[y];
		}
	}
	
	if (!core && siz[x] * 2 >= n) core = x;
}

int main() {
	scanf("%d", &n);
	int u, v;
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &u, &v);
		add(u, v), add(v, u);
	}
	
	getCore(root);
	printf("%d\n", core);
	return 0;
}
