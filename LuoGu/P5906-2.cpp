#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <cmath>

using namespace std;

const int N = 2e5 + 7;

int n, nq;
int a[N]; 

void readDiscrete() {
	scanf("%d", &n); nq = sqrt(n);
	map<int, int> mp;
	int p = 0, t, v;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &t);
		if ((v = mp[t]) == 0) v = mp[t] = ++p;
		a[i] = v;
	}
}

int m;
struct Ques {
	int l, r, i;
	bool operator< (const Ques &q) {
		if (q.l / nq ^ l / nq)
			return l < q.l;
		return r < q.r;
	}
} ques[N];

void readQues() {
	scanf("%d", &m);
	Ques * ptr = ques;
	for (int i = 1; i <= m; ++i) {
		++ptr;
		scanf("%d %d", &ptr->l, &ptr->r);
		ptr->i = i;
	}
	
	sort(ques + 1, ptr + 1);
}

int fi[N], la[N], cur = 0;

void add(int p) {
	int ap = a[p];
	if (fi[ap] == 0 || fi[ap] > p) fi[ap] = p;
	if (la[ap] < p) la[ap] = p;
	cur = max(cur, la[ap] - fi[ap]);
}

// clean [l, r)
void clean(int l, int r) {
	for (int i = l; i < r; ++i) {
		fi[a[i]] = la[a[i]] = 0;
	}
}

int sfi[N], sla[N], scur;
void save(int l, int r) {
	scur = cur;
	for (int i = l; i <= r; ++i) {
		sfi[a[i]] = fi[a[i]];
		sla[a[i]] = la[a[i]];
	}
}

void recover(int l, int r) {
	cur = scur;
	for (int i = l; i <= r; ++i) {
		fi[a[i]] = sfi[a[i]];
		la[a[i]] = sla[a[i]];
	}
}

int res[N];
void work() {
	int lb = -1, bs = nq, r; // bs，下一个块开始的地方 
	Ques * ptr = ques;
	for (int i = 1; i <= m; ++i) {
		++ptr;
		
		if (lb ^ ptr->l / nq) { // 块改变 
			lb = ptr->l / nq;
			bs = (lb + 1) * nq; // [bs, bs + nq)
			r = bs - 1; // add(++r)
			memset(fi, 0, sizeof(fi));
			memset(la, 0, sizeof(fi));
		}
		
		// 左右在同一个块中
		if (ptr->l / nq == ptr->r / nq) {
			cur = 0;
			for (int i = ptr->l; i <= ptr->r; ++i)
				add(i);
			res[ptr->i] = cur;
			clean(ptr->l, ptr->r + 1);
		} else {
			while (r < ptr->r) add(++r);
			save(bs, r);
			int l = bs;
			while (l > ptr->l) add(--l);
			res[ptr->i] = cur;
			clean(l, bs);
			recover(bs, r);
		}
	}
}

int main() {
	readDiscrete();
	readQues();
	work();
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", res[i]);
	}
	return 0;
}
