#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 2e3 + 2, M = N * N;

struct Edge {
	int x, y, w;
	bool operator < (const Edge &e) {
		return w < e.w;
	}
} e[M];

int grp[N];
inline int find(int x) {
	return x == grp[x] ? x : grp[x] = find(grp[x]);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(false);

	int	n;
	cin >> n;

	int idx = 0;
	for (int x, i = 0; i < n; i++) {
		for (int j = i + 1; j <= n; ++j) {
			cin >> x;
			e[idx++] = {i, j, x};
		}
	} sort(e, e + idx);

	long long w = 0;
	for (int i = 0; i <= n; ++i) grp[i] = i;
	for (int i = 0; i < idx; ++i) {
		Edge &c = e[i];
		if (find(c.x) != find(c.y)) {
			grp[find(c.x)] = find(c.y);
			w += c.w;
		}
	}
	cout << w << '\n';
	return 0;
}
