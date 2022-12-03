#include <iostream>
#include <queue>
#include <algorithm>

struct Edge {
	int from, to, w;
	bool operator< (const Edge &e) const {
		return w < e.w;
	}
}; 

const int M = 2e5, N = 5000;
Edge edge[M];

class MergeFindSet {
	private: int grp[N + 1];
	public:
	MergeFindSet() {
		for (int i = 1; i <= N; ++i) grp[i] = i;
	}
	void merge(int x, int y) {
		grp[find(x)] = find(y);
	}
	int find(int x) {
		static int ox; ox = x;
		while (grp[x] != x) x = grp[x];
		return grp[ox] = x;
	}
};

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i) scanf("%d%d%d", &edge[i].from, &edge[i].to, &edge[i].w);
	std::sort(edge, edge + m);
	
	static MergeFindSet mfs;
	
	long long len = 0; 
	for (int i = 0; i < m; ++i) {
		int x = mfs.find(edge[i].from), y = mfs.find(edge[i].to);
		if (x != y) {
			len += edge[i].w;
			mfs.merge(x, y);
		}
	}
	int fa0 = mfs.find(1);
	for (int i = 1; i <= n; ++i) {
		if (fa0 != mfs.find(i)) {
			printf("orz\n");
			return 0;
		}
	}
	
	printf("%lld\n", len);
	return 0;
}
