#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>

const int N = 5e5 + 7;

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

struct Node {
	int prio, val, l, r, siz, cnt;
	inline void init(int val, int pri = 0) {
		if (!pri) prio = rand() * rand();
		this->val = val;
		siz = cnt = 1, l = r = 0;
	}
};

class FHQTreap {
private:
	Node nodes[N * 50];
public:
	int usage;
	FHQTreap() : usage(0) { srand(20040328); };
	
	#define lp(p) nodes[p].l
	#define rp(p) nodes[p].r
	#define cnt(p) nodes[p].cnt
	#define siz(p) nodes[p].siz
	#define prio(p) nodes[p].prio
	#define val(p) nodes[p].val
	
	#define update(p) (siz(p) = siz(lp(p)) + siz(rp(p)) + cnt(p))
	
	inline int clone(int p) {
		nodes[++usage] = nodes[p];
		return usage;
	}
	
	inline void splitVal(int p, int val, int &x, int &y, bool simple = true) {
		if (!p) return (void)(x = y = 0);
		int np = simple ? p : clone(p);
		if (val(p) <= val)
			x = np, splitVal(rp(p), val, rp(x), y, simple), update(x);
		else
			y = np, splitVal(lp(p), val, x, lp(y), simple), update(y);
	}
	
	inline int merge(int x, int y) {
		if (!x | !y) return x | y;
		
		if (prio(x) > prio(y)) {
			rp(x) = merge(rp(x), y);
			return update(x), x;
		} else {
			lp(y) = merge(x, lp(y));
			return update(y), y;
		}
	}
	
	inline int insert(int root, int val, bool simple = false) {
		int x(0), y(0), p(++usage);
		nodes[p].init(val);
		splitVal(root, val, x, y, simple);
		return merge(merge(x, p), y);
	}
	
	inline int remove(int root, int val, bool simple = false) {
		int x(0), y(0), z(0), m(0);
		splitVal(root, val - 1, x, m, simple);
		splitVal(m, val, y, z, simple);
		return merge(x, merge(merge(lp(y), rp(y)), z));
	}
	
	inline int count(int root, int val) {
		int x(0), y(0);
		splitVal(root, val - 1, x, y);
		int res = siz(x);
		return merge(x, y), res;
	}
	
	inline int kth(int root, int k) {
		int p = root; ++k; // exlude first one
		while (true) {
			int sz = siz(lp(p));
			if (k <= sz) p = lp(p);
			else if (k == sz + 1) return val(p);
			else k -= sz + 1, p = rp(p);
		}
		// NEVER REACHED!
		return -1;
	}
	
	inline int getpre(int root, int val) {
		int x(0), y(0), p(0);
		splitVal(root, val - 1, x, y);
		p = x;
		while (rp(p)) p = rp(p);
		return merge(x, y), val(p);
	}
	
	inline int getpost(int root, int val) {
		int x(0), y(0), p;
		splitVal(root, val, x, y);
		p = y;
		while (lp(p)) p = lp(p);
		return merge(x, y), val(p);
	}
};

int main() {
	freopen("P3835_3.in", "r", stdin);
	freopen("P3835.ans", "w", stdout);
	
	static int root[N];
	static FHQTreap treap;
	
	root[0] = treap.insert(root[0], (int)((1ll<<31) - 1), true);
	root[0] = treap.insert(root[0], (int)(-(1ll<<31) + 1), true);
	
	int n, v, opt, x;
	read(n);
	
	for (int i = 1; i <= n; ++i) {
		read(v, opt, x);
		root[i] = root[v];
		// printf("V root = %d\n", root[i]);
		switch(opt) {
			case 1: // insert x
				root[i] = treap.insert(root[i], x); break;
			case 2: // delete x
				root[i] = treap.remove(root[i], x); break;
			case 3: // get x's rank
				printf("%u\n", treap.count(root[i], x));
				break;
			case 4: // get kth
				printf("%d\n", treap.kth(root[i], x));
				break;
			case 5:
				printf("%d\n", treap.getpre(root[i], x));
				break;
			case 6:
				printf("%d\n", treap.getpost(root[i], x));
				break;
		} // end switch opt
		// printf("Root(%d) = %d\n", i, root[i]);
		// treap.prt(root[i]);
	}
	
	return 0;
}