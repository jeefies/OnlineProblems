#include <iostream>
#include <set>
#include <algorithm>

struct RD {
	int x, y, t;
	bool operator< (const RD &r) const {
		return t < r.t;
	}
};

RD rds[100000];

const int N = 1000 + 1; 
class MergeFindSet {
private:
public:
	int grp[N], grp_count;
	void init(int n) {
		grp_count = n;
		for (int i = 0; i <= n; ++i) grp[i] = i;
	}
	
	void merge(int x, int y) {
		int gx = find(x), gy = find(y);
		if (gx != gy) {
			--grp_count;
			grp[gx] = gy;
		}
	}
	
	int find(int x) {
		if (grp[x] != x) return grp[x] = find(grp[x]);
		return x;
	}
};

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", &rds[i].x, &rds[i].y, &rds[i].t);
	}
	
	std::sort(rds, rds + m);
	
	int t = -1;
	static MergeFindSet mfs;
	mfs.init(n);
	for (int i = 0; i < m; ++i) {
		mfs.merge(rds[i].x, rds[i].y);
		if (mfs.grp_count == 1) {
			t = rds[i].t;
			break;
		}
	}
	printf("%d\n", t);
}
