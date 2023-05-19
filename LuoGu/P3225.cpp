#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 1500 + 3;

vector<int> G[N];
#define add(u, v) (G[u].push_back(v))

int dfn[N], low[N], cdfn = 0;
int cut[N], root;
void tarjan(int x, int f) {
	dfn[x] = low[x] = ++cdfn;
	int subs = 0;
	for (int y : G[x]) {
		if (!dfn[y]) {
			tarjan(y, x);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x] && x != root)
				cut[x] = true;
			++subs;
		} else if (y ^ f) low[x] = min(low[x], dfn[y]);
	}

	if (x == root && subs > 1) cut[x] = true;
}

int vis[N];
int bs = 0, cuts = 0;
void dfs(int x) {
	++bs;
	vis[x] = true;
	for (int y : G[x]) {
		if (cut[y] && vis[y] != root) ++cuts, vis[y] = root;
		if (!vis[y] && !cut[y]) dfs(y);
	}
}

inline long long C2(long long x) {
	return (x & 1) ? ((x - 1) / 2 * x) : (x / 2 * (x - 1));
}

bool work(int id) {
	int n;
	cin >> n;
	if (!n) return false;
	for (int i = 0; i < N; ++i) G[i].clear();

	int m = 0;
	for (int u, v, i = 0; i < n; ++i) {
		cin >> u >> v;
		add(u, v), add(v, u);
		if (u > m) m = u;
		if (v > m) m = v;
	}

	fill(cut, cut + m + 1, 0);
	fill(dfn, dfn + m + 1, 0);
	fill(vis, vis + m + 1, 0);
	for (int i = 1; i <= m; ++i) {
		if (!dfn[i]) root = i, tarjan(i, -1);
	}

	long long totSet = 0, sits = 1;
	for (int i = 1; i <= m; ++i) {
		if (!vis[i] && !cut[i]) {
			bs = cuts = 0;
			dfs(root = i);

			if (cuts == 0) {
				totSet += 2;
				sits *= bs * (bs - 1) / 2;
			} else if (cuts == 1) {
				totSet += 1;
				sits *= bs;
			}
		}
	}

	cout << "Case " << id << ": " << totSet << ' ' << sits << '\n';
	return true;
}

int main() {
	// cin.tie(nullptr)->sync_with_stdio(false);

	int id = 0;
	while (work(++id));
}
