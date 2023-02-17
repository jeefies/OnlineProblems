#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

template<typename T>
inline void read(T &x) {
	register char tmp, f(0); x = 0;
	do if ((tmp = getchar()) == '-') f = 1; while (tmp < '0' || '9' < tmp);
	do x = (x<<1) + (x<<3) + (tmp ^ 48), tmp = getchar(); while ('0' <= tmp && tmp <= '9');
	if (f) x = -x;
}
template<typename T, typename ...Args>
inline void read(T &x, Args&... args) {
	read(x), read(args...);
}

typedef unsigned int uint;
const uint INF = 0x7FFFFFFF, N = 3e6 + 7;

// self make Rand uint priority! Maybe a little bit faster....
inline uint Rand() {
	static uint seed = 142857;
	return seed = (uint) seed * 114514LL % 1000000919;
}

struct Node {
	int val;
	uint l, r;
	uint pri, cnt, siz;
	inline void init(int val, uint pri = 0) {
		this->val = val;
		this->pri = pri ? pri : Rand();
		this->cnt = this->siz = 1;
		l = r = 0;
	}
};

class Treap {
private:
	Node nodes[N];
	// cnt is for the number of the nodes
	// root refers to current root.
	//  Remember root may change each time
	uint cnt, root;
public:
	Treap() : cnt(0) {}
	
	#define lp(p) nodes[p].l
	#define rp(p) nodes[p].r
	#define cnt(p) nodes[p].cnt
	#define siz(p) nodes[p].siz
	#define prio(p) nodes[p].pri
	#define val(p) nodes[p].val
	
	inline uint newNode(int val) {
		nodes[++cnt].init(val);
		return cnt;
	}
	
	inline void update(uint p) {
		siz(p) = siz(lp(p)) + siz(rp(p)) + cnt(p);
	}

	// this two rotate operation can maintain the treap like a heap.
	// Make sure the complexity would not turn into O(n)
	inline void leftRotate(uint &p) {
		uint q = rp(p);
		rp(p) = lp(q), lp(q) = p, p = q;
		update(lp(p)), update(p);
	}
	
	inline void rightRotate(uint &p) {
		uint q = lp(p);
		lp(p) = rp(q), rp(q) = p, p = q;
		update(rp(p)), update(p);
	}
	
	// insert the element in the Treap.
	// If there's the same element, increase the count of that.
	void insert(int val) { insert(root, val); }
	inline void insert(uint &p, int val) {
		if (!p) {
			p = newNode(val);
			// printf("New node (p %u) val %d (prio = %u)\n", p, val, prio(p));
			return;
		}
		
		if (val(p) == val) {
			++cnt(p), ++siz(p);
			// ++cnt(p); update(p);
			return;
		} else if (val(p) > val) {
			// into left node
			// printf("In left inserting\n");
			insert(lp(p), val);
			if (prio(p) < prio(lp(p))) rightRotate(p);
		} else {
			// printf("In right inserting\n");
			insert(rp(p), val);
			if (prio(p) < prio(rp(p))) leftRotate(p);
		}
		update(p);
	}
	
	// Remove one element from the treap.
	// But if the count is more than 1, just decrease it is ok.
	void remove(int val) { remove(root, val); }
	inline void remove(uint &p, int val) {
		if (!p) return;
		
		if (val == val(p)) {
			// repeat element, delete one and do nothing
			if (cnt(p) > 1) {
				--cnt(p); update(p);
				// --cnt(p), --siz(p);
				return;
			}
			
			// remove this node!
			if (lp(p) || rp(p)) {
				// has child nodes!
				// no right node or left node's priority is greater than right one's
				if (rp(p) == 0 || prio(lp(p)) > prio(rp(p)))
					rightRotate(p), remove(rp(p), val);
				else
					leftRotate(p), remove(lp(p), val);
				// update(p);
			} else {
				// no child nodes!
				p = 0;
			}
		} else if (val < val(p)) {
			// delete in left node
			remove(lp(p), val);
		} else {
			remove(rp(p), val);
		}
		update(p);
	}
	
	// if include is true, the result can include the count of the element
	uint count(int val, bool include = false) { return count(root, val, include); }
	inline uint count(const uint p, int val, bool include) {
		if (!p) return 0;
		if (val == val(p))
			return siz(lp(p)) + (include ? cnt(p) : 0);
		else if (val < val(p))
			return count(lp(p), val, include);
		else
			return siz(lp(p)) + cnt(p) + count(rp(p), val, include);
	}
	
	int kth(uint k) { return kth(root, k); }
	inline int kth(const uint p, uint k) {
		if (!p) return INF;
		
		uint ls = siz(lp(p)), ms = siz(lp(p)) + cnt(p);
		if (ls >= k) 
			return kth(lp(p), k);
		else if (ms >= k) 
			return val(p);
		return kth(rp(p), k - ms);
	}
	
	int getpre(int val) {
		return kth(count(val));
	}
	
	int getpost(int val) {
		return kth(count(val, true));
	}
	
	#undef lp
	#undef rp
	#undef val
	#undef siz
	#undef cnt
	#undef prio
};

// SB problem!!! LZRNM
int main() {
	static Treap treap;
	treap.insert(-2147483647);
	treap.insert(2147483647);
	
	int n, m, opt, x, last = 0;
	read(m);
	
	while (m--) {
		read(opt, x);
		x ^= last;
		switch(opt) {
			case 5: // insert x
				treap.insert(x); break;
			case 1: // get x's rank
				printf("%u\n", treap.count(x) + 1);
				// ans ^= last = treap.count(x) + 1;
				break;
			case 2: // get kth
				printf("%d\n", treap.kth(x));
				// ans ^= last = treap.kth(x);
				break;
			case 3:
				printf("%d\n", treap.getpre(x));
				// ans ^= last = treap.getpre(x);
				break;
			case 4:
				printf("%d\n", treap.getpost(x));
				// ans ^= last = treap.getpost(x);
				break;
		} // end switch opt
	}
	return 0;
}