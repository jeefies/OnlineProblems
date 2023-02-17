#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

template<typename T>
void readI(T & x) {
	x = 0; T f = 1; char tmp;
	do {
		if ((tmp = getchar()) == '-') f = -1;
	} while (tmp < '0' || '9' < tmp);
	do {
		x = (x<<3) + (x<<1) + tmp - '0', tmp = getchar();
	} while ('0' <= tmp && tmp <= '9');
	x *= f;
}

const int N = 1e6 + 7;

int n, m;
int a[N];

struct Node {
	Node *lp, *rp;
	int val;
} tree[N * 24];
Node * usage = tree;
Node * vers[N] = {nullptr};

inline void build(Node * &p, int l, int r) {
	if (!p) p = ++usage;
	if (l == r) {
		p->val = a[l];
		return;
	}
	
	int mid = (l + r) >> 1;
	build(p->lp, l, mid), build(p->rp, mid + 1, r);
}

inline void change(Node * &p, Node * &q, int l, int r, int loc, int val) {
	if (!p) p = ++usage;
	
	if (l == r) {
		p->val = val;
		return;
	}
	
	int mid = (l + r) >> 1;
	if (loc <= mid) {
		change(p->lp, q->lp, l, mid, loc, val);
		p->rp = q->rp;
	} else {
		change(p->rp, q->rp, mid + 1, r, loc, val);
		p->lp = q->lp;
	}
}

inline int query(Node * p, int l, int r, int i) {
	if (l == r) return p->val;
	
	int mid = (l + r) >> 1;
	if (i <= mid) return query(p->lp, l, mid, i);
	return query(p->rp, mid + 1, r, i);
}

int main() {
	readI(n), readI(m);
	for (int i = 1; i <= n; ++i) readI(a[i]);
	
	build(vers[0], 1, n);
	
	int vi, op, loc, val;
	for (int i = 1; i <= m; ++i) {
		readI(vi), readI(op), readI(loc);
		if (op == 2) {
			// query root vers[i] at loc
			vers[i] = vers[vi];
			printf("%d\n", query(vers[i], 1, n, loc));
		} else {
			// copy from root vers[vi]
			readI(val);
			change(vers[i], vers[vi], 1, n, loc, val);
		}
	}
	return 0;
}