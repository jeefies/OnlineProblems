#include <iostream>

const int N = 5000 + 10;

// merge_find set
class MergeFindSet {
private:
	int grp[N];
public:
	void init(int n) {
		for (int i = 0; i < n; ++i) this->grp[i] = i;
	}
	
	int find(int x) {
		while (this->grp[x] != x) x = this->grp[x];
		return grp[x] = x; 
	}
	
	void merge(int x, int y) {
		this->grp[find(x)] = find(y);
	}
	
	void prt(int n) {
		for (int i = 1; i <= n; ++i)
			printf("%d ", this->grp[i]);
		putchar('\n');
	}
};

static MergeFindSet mfs; 
int main() {
	int n, m, p;
	scanf("%d %d %d", &n, &m, &p);
	mfs.init(n);
	
	int a, b;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &a, &b);
		mfs.merge(a, b); 
	}
	
	for (int i = 0; i < p; ++i) {
		scanf("%d %d", &a, &b);
		printf(mfs.find(a) == mfs.find(b) ? "Yes\n" : "No\n");
	}
	
	return 0;
}
