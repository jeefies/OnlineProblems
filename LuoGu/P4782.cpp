#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>

using namespace std;
const int N = 1e6 + 7;

int n, m;
vector<int> G[N * 2];

inline void add(int u, int v) {
	G[u].push_back(v);
}

stack<int> stk;
vector<int> color;
static int dfn[N * 2], low[N * 2], ins[N * 2], cdfn = 0, ccol = 0;
inline void tarjan(int x) {
	dfn[x] = low[x] = ++cdfn;
	stk.push(x), ins[x] = true;
	for (const int &y : G[x]) {
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (ins[y]) {
			low[x] = min(low[x], dfn[y]);
		}
	}
	
	if (dfn[x] == low[x]) {
		int y; ++ccol;
		do {
			y = stk.top(); stk.pop();
			ins[y] = false, color[y] = ccol;
		} while (y != x);
	}
}

int main() {
	scanf("%d %d", &n, &m);
	color.resize(n * 2 + 1);
	
	int i, a, j, b;
	for (int h = 1; h <= m; ++h) {
		scanf("%d %d %d %d", &i, &a, &j, &b);
		// 减少判断 
		// add(i + n * (a ^ 1), j + n * (b & 1));
		// add(j + n * (b ^ 1), i + n * (a & 1));
		if (a == 0 && b == 0) {
			add(i + n, j), add(j + n, i);
		} else if (a == 0 && b == 1) {
			add(i + n, j + n), add(j, i);
		} else if (a == 1 && b == 0) {
			add(i, j), add(j + n, i + n);
		} else { // a == 1 && b == 1
			add(i, j + n), add(j, i + n);
		}
	}
	
	for (int i = 1; i <= n + n; ++i) {
		if (!dfn[i]) tarjan(i);
	}
	
	for (int i = 1; i <= n; ++i) {
		if (color[i] == color[i + n]) return puts("IMPOSSIBLE"), 0;
	}
	
	puts("POSSIBLE");
	for (int i = 1; i <= n; ++i) {
		// ??? 为什么颜色标色较大的拓扑序较前？ 
		if (color[i] > color[i + n]) printf("1 ");
		else printf("0 ");
	}
	return 0;
}
