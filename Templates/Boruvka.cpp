#include <iostream>
#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;
const int N = 5000 + 3; 

typedef pair<int, int> pii;
vector<pii> G[N];

int grp[N];

void init(int n) {
	for (int i = 1; i <= n; ++i) grp[i] = i;
}

inline int find(int x) {
	return x == grp[x] ? x : grp[x] = find(grp[x]);
}

int link[N], val[N];
int Boruvka(int n) {
	init(n);
	
	int tot = 0;
	int blocks = n;
	while (blocks > 1) {
		fill(val, val + 1 + n, int(1e9));
		
		// search for min 
		for (int w, gy, gx, x = 1; x <= n; ++x) {
			for (auto e : G[x]) {
				w = e.second;
				gy = find(e.first), gx = find(x);
				if (gx ^ gy && w < val[gx]) 
					val[gx] = w, link[gx] = gy;
			}
		}
		
		// connect blocks
		int connectBlocks(0); 
		for (int x = 1; x <= n; ++x) {
			if (grp[x] ^ x || x == find(link[x])) continue;
			++connectBlocks, grp[x] = find(link[x]);
			tot += val[x];
		}
		
		// check for blocks, if no blocks connected, means that 
		// the graph may not be connected! 
		blocks -= connectBlocks;
		if (blocks > 1 && !connectBlocks) return -1;
	}
	return tot;
}

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	int n, m;
	cin >> n >> m;
	
	for (int x, y, w, i(0); i ^ m; ++i) {
		cin >> x >> y >> w;
		G[x].push_back(make_pair(y, w));
		G[y].push_back(make_pair(x, w));
	}
	
	int res = Boruvka(n);
	if (res == -1) puts("orz");
	else cout << res << '\n';
	return 0;
}