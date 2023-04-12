#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>

const int N = 3e6 + 7;

// pointer can not use uint16 (too short!)

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

struct Node {
	uint prio, siz, cnt;
	uint l, r;
	// later we may use lazyRev, lazyChange...
	int val;
	inline void init(int val, uint pri = 0) {
		this->val = val;
		prio = pri ? pri : rand() * rand();
		cnt = siz = 1, l = r = 0;
	}
};

class FHQTreap {
private:
	Node nodes[N];
	uint usage, root;
public:
	FHQTreap() : usage(0) { srand(20040328); };
	
	#define lp(p) nodes[p].l
	#define rp(p) nodes[p].r
	#define cnt(p) nodes[p].cnt
	#define siz(p) nodes[p].siz
	#define prio(p) nodes[p].prio
	#define val(p) nodes[p].val
	
	#define update(p) (siz(p) = siz(lp(p)) + siz(rp(p)) + cnt(p))
	
	// core: splitByVal(p, v, x, y), splitByRank(p, v, x, y), merge(x, y)
	// x, y refers to ltree and rtree when spliting!
	inline void splitByVal(uint p, int val, uint &x, uint &y) {
		if (!p) return (void)(x = y = 0);
		// sync(p) // child node!
		if (val(p) <= val)
			x = p, splitByVal(rp(p), val, rp(p), y);
		else
			y = p, splitByVal(lp(p), val, x, lp(p));
		update(p);
	}
	
	inline void splitByRank(uint p, uint k, uint &x, uint &y) {
		if (!p) return (void)(x = y = 0);
		// sync(p) // child node!
		if (siz(lp(p)) < k)
			x = p, splitByRank(rp(p), k - siz(lp(p)) - cnt(p), rp(p), y);
		else
			y = p, splitByRank(lp(p), k, x, lp(p));
		update(p);
	}
	
	inline uint merge(uint x, uint y) {
		if (!x | !y) return x | y;
		// sync(x), sync(y);
		if (prio(x) > prio(y)) { // big big first!
			rp(x) = merge(rp(x), y);
			return update(x), x;
		} else {
			lp(y) = merge(x, lp(y));
			return update(y), y;
		}
		return -1; // NOT REACHED!
	}
	
	inline void insert(int val) {
		nodes[++usage].init(val);
		uint x(0), y(0);
		splitByVal(root, val, x, y);
		root = merge(merge(x, usage), y);
	}
	
	inline void remove(int val) {
		uint x(0), y(0), z(0), m(0);
		// exclude val!
		splitByVal(root, val - 1, x, m);
		splitByVal(m, val, y, z);
		// tree y's val are all val
		root = merge(merge(x, lp(y)), merge(rp(y), z));
	}
	
	inline uint getRank(int val) {
		uint x(0), y(0), res;
		splitByVal(root, val - 1, x, y);
		res = siz(x) + 1;
		return merge(x, y), res;
	}
	
	inline int kth(uint k) {
		uint x(0), y(0), p;
		splitByRank(root, k, x, y);
		// get max in x is ok
		p = x;
		while (rp(p)) p = rp(p);
		return merge(x, y), val(p);
	}
	
	inline int getpre(int val) {
		uint x(0), y(0), p;
		splitByVal(root, val - 1, x, y);
		p = x; while (rp(p)) p = rp(p);
		return merge(x, y), val(p);
	}
	
	inline int getpost(int val) {
		uint x(0), y(0), p;
		splitByVal(root, val, x, y);
		p = y; while (lp(p)) p = lp(p);
		return merge(x, y), val(p);
	}
};

/*
int main() {
	static FHQTreap treap;
	
	int n, opt, x;
	read(n);
	
	while (n--) {
		read(opt, x);
		switch(opt) {
			case 1: // insert x
				treap.insert(x); break;
			case 2: // delete x
				treap.remove(x); break;
			case 3: // get x's rank
				printf("%u\n", treap.getRank(x));
				break;
			case 4: // get kth
				printf("%d\n", treap.kth(x));
				break;
			case 5:
				printf("%d\n", treap.getpre(x));
				break;
			case 6:
				printf("%d\n", treap.getpost(x));
				break;
		} // end switch opt
	}
	
	return 0;
}
*/

int main() {
	static FHQTreap treap;
	
	int n, m, opt, x, last = 0;
	read(n, m);
	for (int i = 0; i < n; ++i) {
		read(x);
		treap.insert(x);
	}
	
	int ans = 0;
	while (m--) {
		read(opt, x);
		x ^= last;
		switch(opt) {
			case 1: // insert x
				treap.insert(x); break;
			case 2: // delete x
				treap.remove(x); break;
			case 3: // get x's rank
				// printf("%u\n", treap.count(x) + 1);
				ans ^= last = treap.getRank(x);
				break;
			case 4: // get kth
				// printf("%d\n", treap.kth(x));
				ans ^= last = treap.kth(x);
				break;
			case 5:
				// printf("%d\n", treap.getpre(x));
				ans ^= last = treap.getpre(x);
				break;
			case 6:
				// printf("%d\n", treap.getpost(x));
				ans ^= last = treap.getpost(x);
				break;
		} // end switch opt
	}
	printf("%d\n", ans);
	return 0;
}