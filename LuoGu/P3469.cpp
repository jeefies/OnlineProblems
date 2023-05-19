#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;
const int N = 2e5 + 3;
typedef long long lint;

vector<int> G[N];

int n, m;
lint res[N];
int dfn[N], low[N], cut[N], siz[N], cdfn = 0;
int col[N], scc = 0;
int root;
stack<int> stk;
void tarjan(int x, int f) {
	siz[x] = 1;
	dfn[x] = low[x] = ++cdfn;
	lint subs = 0, sum = 0;
	for (int y : G[x]) {
		if (!dfn[y]) {
			tarjan(y, x);
			siz[x] += siz[y];
			low[x] = min(low[x], low[y]);
			if (dfn[x] <= low[y]) {
				res[x] += sum * siz[y];
				sum += siz[y];
				if (x != root) cut[x] = true;
			}
			++subs;
		} else if (y ^ f) {
			low[x] = min(low[x], dfn[y]); 
		}
	}
	
	if (x == root && subs > 1) cut[x] = true;
	res[x] += sum * (n - sum - 1);
}

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	cin >> n >> m;
	for (int x, y, i = 0; i ^ m; ++i) {
		cin >> x >> y;
		G[x].push_back(y), G[y].push_back(x);
	}
	
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) root = i, tarjan(i, -1);
	}
	
	for (int i = 1; i <= n; ++i) {
		cout << ((res[i] + n - 1) << 1) << '\n';
	}
} 
