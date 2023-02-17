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
	inline void clone(Node &n) { val = n.val, siz = n.siz, ch[0] = n.ch[0], ch[1] = n.ch[1]; }
};

const int N = 1e6 + 7;
using std::swap;
class WBLT {
private:
	Node nodes[N * 40];
public:
	int waste[0], windex, usage;
	WBLT() : windex(0), usage(0) {}
	
	inline void _del(int p) {
		waste[windex++] = p;
	}
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
	inline void rotate(int p, bool side) {
		if (!p) return;
		swap(lp(ch(p, side)), rp(ch(p, side)));
		swap(lp(p), rp(p));
		swap(ch(ch(p, side ^ 1), side ^ 1), ch(p, side));
		update(ch(p, side ^ 1)), update(p);
	}
	
	inline void fix(int p, bool simple = true) {
		constexpr float delta = 0.29;
		if (siz(lp(p)) <= siz(p) * delta) rotate(p, 1);
		if (siz(rp(p)) <= siz(p) * delta) rotate(p, 0);
	}
	
	inline void insert(int p, int val) {
		if (siz(p) == 1) {
			int l = _new(val), r = _new(val(p));
			if (val(p) < val) swap(l, r);
			lp(p) = l, rp(p) = r, update(p);
			return;
		}
		insert(val(lp(p)) >= val ? lp(p) : rp(p), val);
		update(p), fix(p);
	}
	
	inline void remove(int p, int val) {
		if (!p) return;
		int side = val(lp(p)) < val ? 1 : 0;
		int &lp = ch(p, side), &rp = ch(p, side ^ 1);
		if (siz(lp) == 1 && val(lp) == val) {
			nodes[p].clone(nodes[rp]);
		} else {
			remove(lp, val), update(p), fix(p);
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


#define RUN() WEAK()
int WEAK() {
	static WBLT wblt;
	
	int n, opt, x, vi;
	scanf("%d", &n);
	
	constexpr int MIN = (int)(-(1ll<<31) + 1), MAX = (int)((1ll<<31) - 1);
	
	static int root[N];
	root[0] = wblt._new(MAX);
	wblt.insert(root[0], MIN);
	int procid = 0;
	
	while (procid++ < n) {
		// scanf("%d %d %d", &vi, &opt, &x);
		// root[procid] = root[vi];
		
		scanf("%d %d", &opt, &x);
		root[procid] = root[procid - 1];
		switch(opt) {
			case 1: // insert x
				wblt.insert(root[procid], x); break;
			case 2: // delete x
				wblt.remove(root[procid], x); break;
			case 3: // get x's rank
				printf("%d\n", wblt.count(root[procid], x));
				break;
			case 4: // get kth
				printf("%d\n", wblt.kth(root[procid], x + 1));
				break;
			case 5:
				printf("%d\n", wblt.getpre(root[procid], x));
				break;
			case 6:
				printf("%d\n", wblt.getpost(root[procid], x));
				break;
		} // end switch opt
	}
	
	return 0;
}
/*
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
*/
int main() {
	RUN();
	return 0;
}
