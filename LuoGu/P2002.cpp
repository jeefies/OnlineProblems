#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

struct Edge {
	int to, next;
};

const int M = 5e5 + 2;
const int N = 1e5 + 2;
Edge edge[M];
int head[N], tot = 0;

int inc[N];

void add(int u, int v) {
	++tot;
	edge[tot].to = v, edge[tot].next = head[u], head[u] = tot;
}

int dfn[N], low[N], vis[N], num = 0;
int color[N], grpC;
stack<int> stk;
void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	vis[x] = true;
	stk.push(x);
	for (int i = head[x]; i; i = edge[i].next) {
		int y = edge[i].to;
		
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (vis[y]) {
			low[x] = min(low[x], low[y]);
		}
	}
	if (low[x] == dfn[x]) {
		++grpC;
		int top;
		do {
			top = stk.top(); stk.pop();
			vis[top] = false;
			
			color[top] = grpC;
			// grps[grpC].push_back(top);
		} while (top != x);
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	int u, v; 
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &u, &v);
		add(u, v);
	}
	
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) tarjan(i);
	}

	for (int x = 1; x <= n; x++) {
		for (int i = head[x]; i; i = edge[i].next) {
			int t = edge[i].to;
			if (color[x] != color[t])
				++inc[color[t]];
		}
	}
	
	int ans = 0;
	for (int i = 1; i <= grpC; ++i) {
		if (inc[i] == 0) {
			++ans;
		}
	}
	
	printf("%d\n", ans);
}
