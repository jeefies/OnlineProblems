#include <iostream>

const int N = 300000 + 7;

struct Edge {
	int to, next;
};

Edge edge[N * 2];
int head[N] = {0}, tot = 0;

void add(int u, int v) {
	++tot;
	edge[tot] = {v, head[u]}, head[u] = tot;
}

int core[N] = {0}, siz[N] = {0}, par[N] = {0};
void work(int x) {
	int y, my = 0, ms = 0;
	siz[x] = 1;
	for (int i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		work(y);
		// printf("Work %d done, core = %d\n", y, core[y]);
		siz[x] += siz[y];
		if (siz[y] > ms) ms = siz[y], my = y;
	}
	
	if (my == 0) {
		core[x] = x;
		return;
	}
	
	my = core[my];
	while (siz[my] * 2 < siz[x]) my = par[my];
	core[x] = my;
}

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	int t;
	for (int i = 2; i <= n; ++i) {
		scanf("%d", &t);
		add(t, i);
		par[i] = t;
	}
	
	work(1);
	for (int i = 1; i <= q; ++i) {
		scanf("%d", &t);
		printf("%d\n", core[t]);
	}
	return 0;
}
