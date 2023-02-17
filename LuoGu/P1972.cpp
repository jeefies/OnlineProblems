#include <cstdio>
#include <algorithm>
#include <cmath>

const int N = 1e6 + 7;

int nq;

struct Ques {
	int l, r, i;
	
	bool operator< (const Ques &q) {
		if (l / nq != q.l / nq)
			return l < 	q.l;
		if (l / nq & 1)
			return r > q.r;
		return r < q.r;
	}
};

Ques ques[N];
int a[N], res[N], exi[N];
int cur;

void add(int p) {
	if (exi[a[p]]++ == 0) ++cur;
}

void del(int p) {
	if (--exi[a[p]] == 0) --cur;
}

int main() {
	int n;
	scanf("%d", &n);
	nq = sqrt(n);
	
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
		
	int m;
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &ques[i].l, &ques[i].r);
		ques[i].i = i;
	}
	
	std::sort(ques + 1, ques + m + 1);
	
	int l = 0, r = 0;
	Ques * ptr = ques + 1;
	for (int i = 1; i <= m; ++i) {
		// printf("move [%d, %d] to [%d, %d]: ", l, r, ptr->l, ptr->r);
		while (l > ptr->l) add(--l);
		while (r < ptr->r) add(++r);
		while (l < ptr->l) del(l++);
		while (r > ptr->r) del(r--);
		
		res[ptr->i] = cur;
		// printf(" %d\n", cur);
		
		++ptr;
	}
	
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", res[i]);
	}
	
	return 0;
}