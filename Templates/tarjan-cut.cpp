#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;
const int N = 2e4 + 7;

vector<int> G[N];
#define add(u, v) (G[u].push_back(v))

bitset<N> cut;
int dfn[N], low[N], cdfn = 0;
int root;
void tarjan(int x, int f) {
	dfn[x] = low[x] = ++cdfn;

	int subs = 0;
	for (auto y : G[x]) {
		if (!dfn[y]) {
			tarjan(y, x);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x] && x != root)
				cut[x] = true;
			++subs;
		} else if (y ^ f) {
			low[x] = min(low[x], dfn[y]);
		}
	}
	if (x == root && subs > 1) cut[x] = true;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	for (int u, v, i = 0; i < m; ++i) {
		cin >> u >> v;
		add(u, v), add(v, u);
	}

	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) {
			root = i;
			tarjan(i, -1);
		}
	}

	int cuts = 0;
	for (int i = 1; i <= n; ++i)  {
		if (cut[i]) ++cuts;
	}
	cout << cuts << '\n';
	for (int i = 1; i <= n; ++i) {
		if (cut[i]) cout << i << ' ';
	}
}
