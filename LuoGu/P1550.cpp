#include <iostream>
#include <algorithm>

using namespace std;
const int N = 10000;

struct Edge {
	int x, y, w;
	bool operator < (const Edge &e) {
		return w < e.w;
	}
} es[100000];

int grp[N], rk[N];
inline void init(int n) {
	for (int i = 1; i <= n; ++i) grp[i] = i, rk[i] = 1;
}

inline int find(int x) {
	return x == grp[x] ? x : grp[x] = find(grp[x]);
} 

inline void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) return;
	// make sure rk[x] >= rk[y]
	if (rk[x] < rk[y]) swap(x, y);
	grp[y] = x;
	if (rk[x] == rk[y]) ++rk[x];
}

int main() {
//	cin.tie(0)->sync_with_stdio(false);
	
	int n;
	cin >> n;
	
	int ec = 0;
	for (int w, i = 1; i <= n; ++i) {
		cin >> w;
		es[ec++] = {0, i, w};
	}
	
	for (int w, i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> w;
			es[ec++] = {i, j, w};
		}
	}
	
	sort(es, es + ec);
	init(n);
	int w = 0, tot = 0;
	for (int i = 0; i < ec && tot <= n; ++i) {
		const Edge &e = es[i];
//		clog << "Try " << e.x << " " << e.y << '\n';
		if (find(e.x) != find(e.y)) {
			w += e.w;
			merge(e.x, e.y);
			++tot;
//			clog << "!! Merged\n";
		}
	}
	cout << w;
}
