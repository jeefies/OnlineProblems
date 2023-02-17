#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

int nq;

struct Ques {
	int l, r, i;
	
	bool operator<(const Ques &q) {
		if (l / nq != q.l / nq)
			return l < q.l;
		if (l / nq & 1)
			return r > q.r;
		return r < q.r;
	}
};

const int N = 2e5 + 7;

int n, m;
int res[N], a[N], v[N], exi[N], cnt[N];
Ques ques[N];
int cur = 0;

void add(int p) {
	int ap = a[p];
	++cnt[++exi[ap]];
	cur = max(cur, exi[ap]);
}

void del(int p) {
	int ap = a[p];
	if (--cnt[exi[ap]] == 0 && cur == exi[ap]) --cur;
	--exi[ap];
}

struct Item {
	int v, i;
	bool operator< (const Item &o) {
		return v < o.v;
	}
};

void discrete() {
	static Item it[N];
	Item * ptr = it;
	for (int i = 1; i <= n; ++i) {
		++ptr;
		ptr->v = a[i], ptr->i = i;
	}
	sort(it + 1, it + 1 + n);
	
	int p = 0;
	for (int i = 1; i <= n; ++i) {
		if (it[i].v != it[i - 1].v) ++p;
		a[it[i].i] = p;
	}	
}

int main() {
	scanf("%d %d", &n, &m);
	nq = sqrt(n);
	
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	
	discrete();
	
	Ques * ptr = ques + 1;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &ptr->l, &ptr->r);
		ptr->i = i, ++ptr;
	}
	sort(ques + 1, ques + 1 + m);
	
	int l = 1, r = 0;
	ptr = ques;
	for (int i = 1; i <= m; ++i) {
		++ptr;
		
		// printf("Move [%d, %d] to [%d, %d] (q %d)\n", l, r, ptr->l, ptr->r, ptr->i);
		while (r < ptr->r) add(++r);
		while (r > ptr->r) del(r--);
		while (l > ptr->l) add(--l);
		while (l < ptr->l) del(l++);
		
		// printf("\tAns update to: %d\n", cur);
		res[ptr->i] = cur;
	}
	
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", -res[i]);
	}
	
	return 0;
}