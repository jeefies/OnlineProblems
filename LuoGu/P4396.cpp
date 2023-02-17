#include <iostream>
#include <algorithm>
#include <cmath>

const int N = 1e5 + 7;

#define lowbit(i) (i & -i)
class BIT {
private:
	int b[N];
public:
	void update(int i, int v) {
		for (; i < N; i += lowbit(i)) b[i] += v;
	}
	
	int query(int i) {
		int r = 0;
		for (; i; i -= lowbit(i)) r += b[i];
		return r;
	}
};

int nq;
struct Ques {
	int l, r, a, b, i;
	bool operator< (const Ques &q) {
		if (l / nq != q.l / nq)
			return l < q.l;
		if ((l / nq) & 1) 
			return r > q.r;
		return r < q.r;
	}
};

BIT cnt, kind;
int exi[N], a[N], resCnt[N], resKind[N];
int n, m;
Ques ques[N];

void add(int p) {
	if (exi[a[p]]++ == 0) {
		kind.update(a[p], 1);
	}
	cnt.update(a[p], 1);
}

void del(int p) {
	if (--exi[a[p]] == 0) {
		kind.update(a[p], -1);
	}
	cnt.update(a[p], -1);
}

int main() {
	scanf("%d %d", &n, &m);
	nq = sqrt(n);
	
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
		
	Ques * ptr = ques + 1;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d %d", &ptr->l, &ptr->r, &ptr->a, &ptr->b);
		ptr->i = i;
		++ptr;
	}
	
	std::sort(ques + 1, ques + 1 + m);
	
	int l = 1, r = 0;
	ptr = ques + 1;
	for (int i = 1; i <= m; ++i) {
		while (l > ptr->l) add(--l);
		while (r < ptr->r) add(++r);
		while (l < ptr->l) del(l++);
		while (r > ptr->r) del(r--);
		
		resCnt[ptr->i] = cnt.query(ptr->b) - cnt.query(ptr->a - 1);
		resKind[ptr->i] = kind.query(ptr->b) - kind.query(ptr->a - 1);
		++ptr;
	}
	
	for (int i = 1; i <= m; ++i) {
		printf("%d %d\n", resCnt[i], resKind[i]);
	}
	
	return 0;
}