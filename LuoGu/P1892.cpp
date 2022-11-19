#include <iostream>
#include <cstring>

const int N = 1e4;

class MergeFindSet {
private:
	int grp[N];
public:
	void init(int n) {
		for (int i = 1; i <= n; ++i) grp[i] = i;
	}
	
	int find(int x) {
		while (grp[x] != x) x = grp[x];
		return grp[x] = x;
	}
	
	void merge(int x, int y) {
		grp[find(x)] = find(y);
	}
	
	void prt(int n) {
		for (int i = 1; i <= n; ++i)
			printf("%d ", grp[i]);
		putchar('\n');
	}
};

int n;

static MergeFindSet mfs;
static int ems[N] = {0};
int main() {
	int m;
	scanf("%d %d", &n, &m);
	mfs.init(n);
	
	char opt; int p, q;
	for (int i = 0; i < m; ++i) {
		std::cin >> opt >> p >> q;
		if (opt == 'F') {
			mfs.merge(p, q); // 将两个friend集合并 
		} else if (opt == 'E') {
			// 和他的上一个仇人合并成朋友
			if (ems[p]) mfs.merge(q, ems[p]);
			ems[p] = q;
			if (ems[q]) mfs.merge(p, ems[q]);
			ems[q] = p; 
		}
		
		// mfs.prt(n);
	}
	
	int maxgrp = 0;
	for (int i = 1; i <= n; ++i) {
		if (i == mfs.find(i)) ++maxgrp;
	}
	
	printf("%d\n", maxgrp);
}
