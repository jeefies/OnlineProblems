#include <iostream>
#include <cstring>
#include <algorithm>
#include <climits>

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

constexpr int N = 3e6 + 7;

typedef unsigned int uint;
struct Node {
	int val;
	uint siz, ch[2];
	inline void init(int val) {
		this->val = val;
		siz = 1, ch[0] = ch[1] = 0;
	}
	
	inline constexpr void clear() {
		val = siz = ch[0] = ch[1] = 0;
	}

	inline constexpr void copy(Node &node) {
		this->val = node.val;
		siz = node.siz;
		ch[0] = node.ch[0], ch[1] = node.ch[1];
	}
};

// #define inline constexpr inline
using std::swap;
class WBLT {
private:
	Node nodes[N];
	uint unused[N], unusedAt, usage;
	uint root;
public:
	#define ch(p, k) nodes[p].ch[k]
	#define lp(p) ch(p, 0)
	#define rp(p) ch(p, 1)
	#define siz(p) nodes[p].siz
	#define val(p) nodes[p].val
	
	WBLT() : unusedAt(0), usage(0), root(0) {
		root = _new(INT_MAX);
	}
	
	inline uint _new(int val) {
		uint p = unusedAt ? unused[--unusedAt] : ++usage; nodes[p].init(val);
		return p;
	}
	
	inline void _del(uint p) {
		nodes[p].clear();
		unused[unusedAt++] = p;
	}
	
	inline uint clone(uint p) {
		uint q = unusedAt ? unused[--unusedAt] : ++usage; nodes[q].copy(nodes[p]);
		return q;
	}
	
	inline void update(uint p) {
		siz(p) = siz(lp(p)) + siz(rp(p));
		val(p) = val(rp(p));
	}
	
	inline uint count(int val) {
		uint p(root), cnt(0);
		while (true) {
			if (siz(p) == 1) return cnt;
			else if (val(lp(p)) >= val) p = lp(p);
			else cnt += siz(lp(p)), p = rp(p);
		}
	}
	
	inline int kth(uint k) {
		uint p(root);
		while (true) {
			if (siz(p) == 1) return k == 1 ? val(p) : -1; // -1: not found!
			else if (siz(lp(p)) >= k) p = lp(p);
			else k -= siz(lp(p)), p = rp(p);
		}
	}
	
	inline int getpre(int val) {
		return kth(count(val));
	}
	
	inline int getpost(int val) {
		return kth(count(val + 1) + 1);
	}
	
	// 0 for left, 1 for right
	inline void rotate(uint p, bool side) {
		if (!p) return;
		swap(lp(ch(p, side)), rp(ch(p, side)));
		swap(lp(p), rp(p));
		swap(ch(ch(p, side ^ 1), side ^ 1), ch(p, side));
		update(ch(p, side ^ 1)), update(p);
	}
	
	// fix has something wrong!
	inline void fix(uint p) {
		if (!p) return;
		
		constexpr float alpha = 0.29;
		int d;
		if (siz(p) <= 1) return;
		if (siz(lp(p)) < siz(p) * alpha) d = 1; // right too big
		else if (siz(rp(p)) < siz(p) * alpha) d = 0; // left too big
		else return; // balanced
		uint k = ch(p, d);
		if (siz(ch(k, d ^ 1)) * (1 - alpha) >= siz(k) * (1 - 2 * alpha)) // child not balanced
			rotate(k, d ^ 1);
		rotate(p, d);
		return;
	}
	
	inline void insert(int val) { insert(root, val); }
	inline void insert(uint p, int val) {
		if (siz(p) == 1) {
			uint l = _new(val(p)), r = _new(val);
			if (val(l) > val(r)) std::swap(l, r);
			lp(p) = l, rp(p) = r;
			return update(p);
		}
		
		insert(val(lp(p)) >= val ? lp(p) : rp(p), val);
		update(p), fix(p);
	}
	
	inline void remove(int val) { remove(root, val); }
	inline void remove(uint p, int val) {
		if (!p) return;
		uint lp = lp(p), rp = rp(p);
		if (val(lp) >= val) {
			if (siz(lp) == 1 && val(lp) == val) {
				nodes[p].copy(nodes[rp]);
				_del(lp), _del(rp);
			} else {
				remove(lp, val), update(p), fix(p);
			} 
		} else {
			if (siz(rp) == 1 && val(rp) == val) {
				nodes[p].copy(nodes[lp]);
				_del(lp), _del(rp);
			} else {
				remove(rp, val), update(p), fix(p);
			}
		}
	}
	
	void prt() { prt(root); };
	inline void prt(uint p) {
		printf("In node (%u), val = %d, siz = %u\n", p, val(p), siz(p));
		
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
	
	inline uint merge(uint x, uint y) {
		if (!x | !y) return fix(x | y), x | y;
		// make sure val(x) <= val(y)
		if (val(x) > val(y)) swap(x, y);
		uint p = _new(val(y));
		fix(x), fix(y); // maybe useless
		lp(p) = x, rp(p) = y;
		return fix(p), p;
	}
	
	// split by val, x contains elements smaller than val, y contains elements greater than val
	inline void split(uint p, int val, uint &x, uint &y) {
		if (siz(p) == 1) {
			if (val(p) <= val) x = p, y = 0;
			else x = 0, y = p;
			return;
		}
		
		if (val(lp(p)) < val) {
			split(rp(p), val, x, y);
			x = merge(lp(p), x), _del(p);
		} else { // val(lp(p)) >= val
			split(lp(p), val, x, y);
			y = merge(y, rp(p)), _del(p);
		}
	}
};
#define RUN() STRONG()
int WEAK() {
	freopen("P3369_7.in", "r", stdin);
	freopen("P3369.out", "w", stdout);
	
	static WBLT wblt;
	
	int n, opt, x;
	scanf("%d", &n);
	
	int procid = 0;
	while (procid++ < n) {
		scanf("%d %d", &opt, &x);
		// proc 36 is wrong in 7
		// printf("Proc %d (%d, %d)\n", procid, opt, x);
		switch(opt) {
			case 1: // insert x
				wblt.insert(x); break;
			case 2: // delete x
				wblt.remove(x); break;
			case 3: // get x's rank
				printf("%u\n", wblt.count(x) + 1);
				break;
			case 4: // get kth
				printf("%d\n", wblt.kth(x));
				break;
			case 5:
				printf("%d\n", wblt.getpre(x));
				break;
			case 6:
				printf("%d\n", wblt.getpost(x));
				break;
		} // end switch opt
		// wblt.prt();
	}
	
	return 0;
}
int STRONG() {
	static WBLT wblt;
	
	int n, m, opt, x, last = 0;
	read(n, m);
	for (int i = 0; i < n; ++i) {
		read(x);
		wblt.insert(x);
	}
	
	int ans = 0;
	while (m--) {
		read(opt, x);
		x ^= last;
		switch(opt) {
			case 1: // insert x
				wblt.insert(x); break;
			case 2: // delete x
				wblt.remove(x); break;
			case 3: // get x's rank
				// printf("%u\n", wblt.count(x) + 1);
				ans ^= last = wblt.count(x) + 1;
				break;
			case 4: // get kth
				// printf("%d\n", wblt.kth(x));
				ans ^= last = wblt.kth(x);
				break;
			case 5:
				// printf("%d\n", wblt.getpre(x));
				ans ^= last = wblt.getpre(x);
				break;
			case 6:
				// printf("%d\n", wblt.getpost(x));
				ans ^= last = wblt.getpost(x);
				break;
		} // end switch opt
	}
	printf("%d\n", ans);
	return 0;
}

int main() {
	RUN();
	return 0;
}
