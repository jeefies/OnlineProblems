#include <iostream>
#include <cstring>
#include <algorithm>
#include <climits>

// FAILED!

template<typename T>
inline void read(T &x) {
	char f(x = 0), tmp;
	do if ((tmp = getchar()) == '-') f = 1; while (tmp < '0' || '9' < tmp);
	do x = (x<<3) + (x<<1) + (tmp^48), tmp = getchar(); while ('0' <= tmp /*&& tmp <= '9'*/);
	if (f) x = -x;
}
template<typename T, typename ...Args>
inline void read(T &x, Args&... args) {
	read(x), read(args...);
}

class Node {
public:
	int val, siz, ch[2];
	inline void clear() { val = siz = ch[0] = ch[1] = 0; }
	inline void init(int val) { this->val = val, siz = 1, ch[0] = ch[1] = 0; }
	inline void clone(Node &n) { *this = n; }
};

const int N = 1e6 + 7;
using std::swap;
class WBLT {
private:
	Node nodes[N * 20];
	int waste[N * 2], windex, usage;
public:
	WBLT() : windex(0), usage(0) {}
	
	inline void _del(int p) { waste[windex++] = p; }
	inline int _new(int val) {
		int p = windex ? waste[--windex] : ++usage;
		nodes[p].init(val);
		return p;
	}
	
	inline int _new(Node &n) {
		int p = windex ? waste[--windex] : ++usage;
		nodes[p].clone(n);
		return p;
	}
	#define ch(p, s) nodes[p].ch[s]
	#define lp(p) ch(p, 0)
	#define rp(p) ch(p, 1)
	#define val(p) nodes[p].val
	#define siz(p) nodes[p].siz
	#define update(p) (val(p) = val(rp(p)), siz(p) = siz(lp(p)) + siz(rp(p)))
	inline void rotate(int p, bool side, bool simple = true) {
		if (!p) return;
		if (!simple) ch(p, side) = _new(nodes[ch(p, side)]);
		// ch(p, side ^ 1) = _new(nodes[ch(p, side ^ 1)]);
		
		swap(lp(ch(p, side)), rp(ch(p, side)));
		swap(lp(p), rp(p));
		swap(ch(ch(p, side ^ 1), side ^ 1), ch(p, side));
		update(ch(p, side ^ 1)), update(p);
	}
	
	inline void fix(int p, bool simple = true) {
		constexpr float delta = 0.29;
		if (siz(lp(p)) <= siz(p) * delta) rotate(p, 1, simple);
		if (siz(rp(p)) <= siz(p) * delta) rotate(p, 0, simple);
	}
	
	inline void insert(int &p, int val, bool simple = true) {
		if (!simple) p = _new(nodes[p]);
		if (siz(p) == 1) {
			int l = _new(val), r = _new(val(p));
			if (val(p) < val) swap(l, r);
			lp(p) = l, rp(p) = r, update(p);
			return;
		}
		insert(val(lp(p)) >= val ? lp(p) : rp(p), val, simple);
		update(p), fix(p);
	}
	
	inline void remove(int &p, int val, bool simple = true) {
		if (!p) return;
		if (!simple) p = _new(nodes[p]);
		
		int side = val(lp(p)) < val ? 1 : 0;
		int &lp = ch(p, side), &rp = ch(p, side ^ 1);
		if (siz(lp) == 1 && val(lp) == val) {
			nodes[p].clone(nodes[rp]);
		} else {
			remove(lp, val, simple), update(p), fix(p);
		}
	}
	
	inline int count(int p, int val) {
		int cnt(0);
		while (true) {
			if (siz(p) == 1) return cnt;
			else if (val(lp(p)) >= val) p = lp(p);
			else cnt += siz(lp(p)), p = rp(p);
		}
	}
	
	inline int kth(int p, int k) {
		while (true) {
			if (siz(p) == 1) return k == 1 ? val(p) : -1; // -1 not found!
			else if (siz(lp(p)) >= k) p = lp(p);
			else k -= siz(lp(p)), p = rp(p);
		}
	}
	
	inline int getpre(int p, int val) {
		return kth(p, count(p, val));
	}
	inline int getpost(int p, int val) {
		return kth(p, count(p, val + 1) + 1);
	}
	
	inline void prt(int p) {
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
};

int main() {
	static WBLT wblt;
	
	int n, m, opt, x, last = 0;
	static int root[N];
	read(n, m);
	
	root[m] = wblt._new(INT_MAX);
	for (int i = 0; i < n; ++i) {
		read(x);
		wblt.insert(root[m], x);
	}
	
	int ans = 0;
	while (m--) {
		read(opt, x);
		x ^= last;
		root[m] = root[m + 1];
		switch(opt) {
			case 1: // insert x
				wblt.insert(root[m], x, false); break;
			case 2: // delete x
				wblt.remove(root[m], x, false); break;
			case 3: // get x's rank
				ans ^= last = wblt.count(root[m], x) + 1;
				break;
			case 4: // get kth
				ans ^= last = wblt.kth(root[m], x);
				break;
			case 5:
				ans ^= last = wblt.getpre(root[m], x);
				break;
			case 6:
				ans ^= last = wblt.getpost(root[m], x);
				break;
		} // end switch opt
	}
	printf("%d\n", ans);
	return 0;
}