#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const int N = 2e6 + 7;

int n, nq, m;
int a[N];

void readDiscrete() {
	static struct Item {
		unsigned int v, i;
	} it[N];
	
	Item * ptr = it;
	for (int i = 1; i <= n; ++i) {
		++ptr;
		scanf("%u", &ptr->v);
		ptr->i = i;
	}
	
	std::sort(it + 1, it + 1 + n, [](const Item & a, const Item & b) {
		return a.v < b.v;
	});
	
	int p = 0;
	for (int i = 1; i <= n; ++i) {
		if (it[i].v != it[i - 1].v) ++p;
		a[it[i].i] = p;
	}
}

struct Ques {
	int l, r, i;
	bool operator< (const Ques &q) {
		if (l / nq ^ q.l / nq)
			return l < q.l;
		return r < q.r;
	}
};

int res[N];
Ques ques[N];

int cur = 0, first[N], last[N];

void clear() {
	cur = 0;
	memset(last, 0, sizeof(last));
	memset(first, 0, sizeof(first));
}

void radd(int p) {
	int ap = a[p];
	if (!first[ap]) first[ap] = p; // avoid first appear!
	last[ap] = p;
	cur = max(cur, p - first[ap]);
}

void ladd(int p) {
	int ap = a[p];
	if (!last[ap]) last[ap] = p;
	first[ap] = p;
	cur = max(cur, last[ap] - p);
}

int bfirst[N], blast[N], prev_cur;
void backup(int l, int r) {
	prev_cur = cur;
	int ap;
	for (int i = l + 1; i <= r; ++i) {
		ap = a[i];
		bfirst[ap] = first[ap], blast[ap] = last[ap];
	}
}

void recover(int pl, int l, int r) {
	// clear [pl, l], add backup.
	int ap;
	for (int i = pl; i <= l; ++i) {
		ap = a[i];
		first[ap] = last[ap] = 0;
	}
	
	cur = prev_cur;
	for (int i = l + 1; i <= r; ++i) {
		ap = a[i];
		first[ap] = bfirst[ap], last[ap] = blast[ap];
	}
}

int main() {
	scanf("%d", &n);
	nq = sqrt(n);
	readDiscrete();
	
	scanf("%d", &m);
	Ques * ptr = ques;
	for (int i = 1; i <= m; ++i) {
		++ptr;
		scanf("%d %d", &ptr->l, &ptr->r);
		ptr->i = i;
	}
	std::sort(ques + 1, ques + 1 + m);
	
	ptr = ques;
	int bl = -1, l = -1, r = -1;
	for (int i = 1; i <= m; ++i) {
		++ptr;
		
		if (ptr->l / nq != bl) {
			// another block, clear all data.
			cur = 0;
			for (int i = l + 1; i <= r; ++i) first[a[i]] = last[a[i]] = 0;
			
			bl = ptr->l / nq;
			r = (bl + 1) * nq - 1, l = r;
		}
		
		if (ptr->l / nq == ptr->r / nq) {
			// the same block
			cur = 0;
			for (int i = ptr->l; i <= ptr->r; ++i)
				radd(i);
			res[ptr->i] = cur;
			
			// clear, no need to backup
			for (int i = ptr->l; i <= ptr->r; ++i) {
				last[a[i]] = first[a[i]] = 0;
			}
			
			continue;
		}
		
		while (r < ptr->r) radd(++r); // add (l, r]
		backup(l, r);
		for (int i = l; i >= ptr->l; --i) ladd(i); // add [ptr->l, l]
		res[ptr->i] = cur;
		recover(ptr->i, l, r);
	}
	
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", res[i]);
	}
	
	return 0;
}