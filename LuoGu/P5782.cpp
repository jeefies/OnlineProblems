#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;
const int N = 1e5;

vector<int> G[N];
#define add(u, v) (G[u].push_back(v))

int col[N], scc = 0;
int dfn[N], low[N], ins[N], cdfn = 0;
stack<int> stk;
void tarjan(int x) {
	dfn[x] = low[x] = ++cdfn;
	ins[x] = true, stk.push(x);
	
	for (int y : G[x]) {
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (ins[y]) {
			low[x] = min(low[x], dfn[y]);
		}
	}
	
	if (low[x] == dfn[x]) {
		int y = ++scc;
		do {
			y = stk.top(); stk.pop();
			ins[y] = false, col[y] = scc;
		} while (x ^ y);
	}
} 

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	int n, m;
	cin >> n >> m;
	
	// x Ñ¡£¬x+shift ²»Ñ¡ 
	int shift = n << 1;
	for (int i = 1; i <= n; ++i) {
		int u = (i << 1) - 1, v = (i << 1);
		add(u, v + shift), add(v, u + shift);
		add(u + shift, v), add(v + shift, u);
	}
	for (int x, y, i = 0; i < m; ++i) {
		cin >> x >> y;
		add(x, y + shift), add(y, x + shift);
	}
	
	for (int i = 1, ie = (n << 2); i <= ie; ++i) {
		if (!dfn[i]) tarjan(i);
	}
	
	for (int i = 1, ie = (n << 1); i <= ie; ++i) {
		if (col[i] == col[i + shift]) return cout << "NIE\n", 0; 
		if (i & 1 && col[i] == col[i + 1]) return cout << "NIE\n", 0;
	}
	
	for (int i = 1, ie = (n << 1); i <= ie; ++i) {
		if (col[i] < col[i + shift]) cout << i << '\n'; 
	}
	return 0;
}
