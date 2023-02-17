#include <iostream>
#include <algorithm>
#include <cstring>

template<typename T>
inline void read(T &x) {
	register char tmp, f(0); x = 0;
	do { if ((tmp = getchar()) == '-') f = 1; } while (tmp < '0' || '9' < tmp);
	do { x = (x<<1) + (x<<3) + (tmp ^ 48), tmp = getchar(); } while ('0' <= tmp && tmp <= '9');
	if (f) x = -x;
}
template<typename T, typename ...Args>
inline void read(T &x, Args&... args) { read(x), read(args...); }

typedef unsigned int uint;

uint Rand() {
	return 1u * rand() * rand();
}

const int N = 5e5 + 7;

struct Node {
	int l, r, siz, val;
	uint prio;
	short revTag;
	inline void init(int val, int pri = 0) {
		prio = pri ? pri : rand() * rand();
		this->val = val;
		siz = 1, l = r = 0;
	}
};

class Treap {
private:
	Node nodes[N];
public:
	int usage, root;
	Treap() : usage(0), root(0) {
		srand(20040328);
	}
	
	inline int newNode(int val) {
		nodes[++usage].init(val);
		return usage;
	}
	
	#define val(p) nodes[p].val
	#define lp(p) nodes[p].l
	#define rp(p) nodes[p].r
	#define cnt(p) 1
	#define siz(p) nodes[p].siz
	#define prio(p) nodes[p].prio
	#define rev(p)  nodes[p].revTag
	
	inline void sync(int p) {
		if (rev(p)) {
			std::swap(lp(p), rp(p));
			if (lp(p)) rev(lp(p)) ^= 1;
			if (rp(p)) rev(rp(p)) ^= 1;
			rev(p) = false;
		}
	}
	#define update(p) (siz(p) = siz(lp(p)) + siz(rp(p)) + 1)
	
	void split(int p, int k, int &x, int &y) {
		if (!k)
			return y = p, (void)(x = 0);
		if (!p)
			return (void)(x = y = 0);
		sync(p);
		if (siz(lp(p)) < k)
			x = p, split(rp(p), k - siz(lp(p)) - 1, rp(x), y);
		else
			y = p, split(lp(p), k, x, lp(y));
		update(p);
	}
	
	int merge(int x, int y) {
		if (!x | !y) return x | y;
		if (prio(x) > prio(y)) {
			sync(x), rp(x) = merge(rp(x), y);
			return update(x), x;
		} else {
			sync(y), lp(y) = merge(x, lp(y));
			return update(y), y;
		}
	}
	
	void mark(int l, int r) {
		int x, y, z;
		split(root, l - 1, x, y);
		split(y, r - l + 1, y, z);
		rev(y) ^= 1;
		root = merge(merge(x, y), z);
	}
	
	inline void prt(uint p) {
		printf("In node (%u), val = %d, cnt, siz = %u, %u\n", p, val(p), cnt(p), siz(p));
		
		if (lp(p)) {
			printf("(%u) into left:\n", p);
			prt(lp(p));
			printf("(%u) left out\n\n", p);
		}
		
		if (rp(p)) {
			printf("(%u) into right:\n", p);
			prt(rp(p));
			printf("(%u) right out\n\n", p);
		}
	}
	
	void output() { output(root); }
	inline void output(int p) {
		if (!p) return;
		sync(p);
		output(lp(p)), printf("%d ", val(p)), output(rp(p));
	}
};

int main() {
	static Treap treap;
	
	int n, m;
	read(n, m);
	
	for (int i = 1; i <= n; ++i) {
		int np = treap.newNode(i);
		treap.root = treap.merge(treap.root, np);
	}
	
	// treap.prt(treap.root);
	int l, r;
	for (int i(0); i ^ m; ++i) {
		read(l, r);
		treap.mark(l, r);
	}
	treap.output();
	return 0;
}