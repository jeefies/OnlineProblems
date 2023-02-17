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

struct Node {
	int val;
	uint fa, siz, cnt;
	uint ch[2];
	inline void init(int val, uint fa) {
		this->val = val, this->fa = fa;
		siz = cnt = 1, ch[0] = ch[1] = 0;
	}
};

class Splay {
private:
	Node nodes[N];
public:
	uint cnt, root, splayTarget;
	Splay() : cnt(0), root(0) {}
	
	#define fa(x) nodes[x].fa
	#define ch(x) nodes[x].ch
	#define lp(x) ch(x)[0]
	#define rp(x) ch(x)[1]
	// 0 for left, 1 for right
	#define side(x) (x == rp(fa(x)))
	#define cnt(x) nodes[x].cnt
	#define siz(x) nodes[x].siz
	#define val(x) nodes[x].val
	
	// update current node's information
	#define update(x) (siz(x) = siz(lp(x)) + siz(rp(x)) + cnt(x))
	
	// rotate x to it's father's position.
	inline void rotate(uint x) {
		uint y = fa(x), z = fa(y), s = side(x);
		if (z) ch(z)[side(y)] = x; // update grandparent
		ch(y)[s] = ch(x)[s ^ 1]; // change y's child node
		if (ch(x)[s ^ 1]) fa(ch(x)[s ^ 1]) = y; // update child node
		ch(x)[s ^ 1] = y; // change x's child node
		fa(x) = z, fa(y) = x; // update child's father
		update(y), update(x); // update x, y's information
	}
	
	// we need to splay splayTarget to root!
	inline void splay() {
		uint &x = splayTarget;
		// printf("Before splay (target = %u)\n", st);
		// prt();
		// if st is not root
		while (fa(x)) {
			uint y = fa(x), z = fa(y);
			if (z) rotate(side(x) == side(y) ? y : x);
			rotate(x);
		}
		root = x;
		// printf("After splay:\n");
		// prt();
	}
	
	void insert(int val) {
		insert(root, 0, val);
		splay();
	}
	inline void insert(uint & p, uint from, int val) {
		if (!p) {
			nodes[p = ++cnt].init(val, from);
			splayTarget = p;
			return;
		}
		
		if (val(p) == val) {
			splayTarget = p, ++cnt(p), ++siz(p);
		} else if (val(p) > val) { // into left node
			insert(lp(p), p, val);
		} else { // into right node
			insert(rp(p), p, val);
		}
		update(p);
	}
	
	int kth(uint k) {
		int val = kth(root, k);
		splay();
		return val;
	}
	inline int kth(const uint p, uint k) {
		// if (!p) return /*printf("Not found kth(%u)\n", k),*/ 1; // not found! why?
		
		if (p) splayTarget = p;
		uint ls = siz(lp(p)), ms = siz(lp(p)) + cnt(p);
		if (ls < k && k <= ms)
			return val(p);
		if (k <= ls)
			if (lp(p)) return kth(lp(p), k);
			else return val(p);
		else
			if (rp(p)) return kth(rp(p), k - ms);
			else return val(p);
		// NOT REACHED!
		return -1;
	}
	
	uint count(int val, bool include = false) {
		uint c = count(root, val, include); // splay after counting!
		splay();
		return c;
	}
	uint count(const uint p, int val, bool include) {
		if (!p) return 0; // not found!
		
		splayTarget = p;
		if (val(p) > val) // this node is the target
			return count(lp(p), val, include);
		else if (val(p) < val) // into left node
			return count(rp(p), val, include) + siz(lp(p)) + cnt(p);
		else
			return siz(lp(p)) + (include ? cnt(p) : 0);
		// NOT REACHED!
		return -1;
	}
	
	int getpre(int val) {
		uint c(count(val));
		return kth(c);
	}
	
	int getpost(int val) {
		uint c(count(val, true));
		return kth(c + 1);
	}
	
	void remove(int val) {
		uint c = count(val); // splay val's node to root
		if (val(root) != val) return;
		// we can just decrease the count!
		if (cnt(root) > 1) {
			--cnt(root), update(root);
			return;
		}
		// we need to delete this element!
		
		// if one of the child node is not exists, just make exists one to root is ok
		if (!(lp(root) && rp(root))) {
			root = lp(root) ? lp(root) : rp(root);
			fa(root) = 0;
			return;
		}
		uint oldRoot = root;
		// else, we need to splay it's pre node here, and connect them is ok
		kth(c);
		rp(root) = rp(oldRoot), fa(rp(root)) = root;
		update(root);
	}
	
	void prt() { prt(root); };
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
};


/*
int main() {
	static Splay splay;
	
	int n, opt, x;
	read(n);
	
	while (n--) {
		read(opt, x);
		switch(opt) {
			case 1: // insert x
				splay.insert(x); break;
			case 2: // delete x
				splay.remove(x); break;
			case 3: // get x's rank
				printf("%u\n", splay.count(x) + 1);
				break;
			case 4: // get kth
				printf("%d\n", splay.kth(x));
				break;
			case 5:
				printf("%d\n", splay.getpre(x));
				break;
			case 6:
				printf("%d\n", splay.getpost(x));
				break;
		} // end switch opt
	}
	
	return 0;
}
*/

int main() {
	static Splay splay;
	
	int n, m, opt, x, last = 0;
	read(n, m);
	for (int i = 0; i < n; ++i) {
		read(x);
		splay.insert(x);
	}
	
	int ans = 0;
	while (m--) {
		read(opt, x);
		x ^= last;
		switch(opt) {
			case 1: // insert x
				splay.insert(x); break;
			case 2: // delete x
				splay.remove(x); break;
			case 3: // get x's rank
				// printf("%u\n", splay.count(x) + 1);
				ans ^= last = splay.count(x) + 1;
				break;
			case 4: // get kth
				// printf("%d\n", splay.kth(x));
				ans ^= last = splay.kth(x);
				break;
			case 5:
				// printf("%d\n", splay.getpre(x));
				ans ^= last = splay.getpre(x);
				break;
			case 6:
				// printf("%d\n", splay.getpost(x));
				ans ^= last = splay.getpost(x);
				break;
		} // end switch opt
	}
	printf("%d\n", ans);
	return 0;
}
