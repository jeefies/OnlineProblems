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
public:
	Node nodes[N * 40];
	int usage;
	WBLT() : usage(0) {}
	
	inline int _new(int val) {
		nodes[++usage].init(val);
		return usage;
	}
	
	inline int _new(Node &n) {
		nodes[++usage].clone(n);
		return usage;
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
	
	inline void fix(int p) {
		constexpr float alpha = 0.29;
		if (!p) return;
		int d;
		if (siz(p) <= 1) return;
		if (siz(lp(p)) < siz(p) * alpha) d = 1; // right too big
		else if (siz(rp(p)) < siz(p) * alpha) d = 0; // left too big
		else return; // balanced
		int k = ch(p, d);
		if (siz(ch(k, d ^ 1)) * (1 - alpha) >= siz(k) * (1 - 2 * alpha)) // child not balanced
			rotate(k, d ^ 1);
		rotate(p, d);
		return;
	}
	
	// copy q to p, like segment tree!
	inline void insert(int &p, int &q, int val) {
		if (!p) p = ++usage;
		
		if (siz(q) == 1) { // insert here
			int val2 = val(q);
			// make sure val <= val2
			if (val2 < val) swap(val, val2);
			int l = _new(val), r = _new(val2);
			lp(p) = l, rp(p) = r, update(p);
			fix(p);
			return;
		}
		
		if (val(lp(q)) >= val) { // into left
			rp(p) = _new(nodes[rp(q)]); // avoid fix error
			insert(lp(p), lp(q), val);
		} else { // into right
			lp(p) = _new(nodes[lp(q)]);
			insert(rp(p), rp(q), val);
		}
		update(p);
		fix(p);
	}
	
	// copy q to p
	inline void remove(int &p, int &q, int val) {
		if (!q) return;
		if (!p) p = ++usage;
		
		int side = val(lp(q)) < val ? 1 : 0;
		if (siz(ch(q, side)) == 1 && val(ch(q, side)) == val) {
			nodes[p].clone(nodes[ch(q, side ^ 1)]);
		} else {
			ch(p, side ^ 1) = _new(nodes[ch(q, side ^ 1)]);
			remove(ch(p, side), ch(q, side), val), update(p), fix(p);
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
		printf("Kth(%d, %d):\n", p, k);
		while (true) {
			if (siz(p) == 1) return k == 1 ? val(p) : -1; // -1 not found!
			else if (siz(lp(p)) >= k) {
				p = lp(p);
				printf("Into left ");
			} else {
				k -= siz(lp(p)), p = rp(p);
				printf("Into right ");
			}
			printf("%d (val %d), k rest %d\n", p, val(p), k);
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
	freopen("P3835_3.in", "r", stdin);
	freopen("P3835.out", "w", stdout);
	
	static WBLT wblt;
	
	int n, vi, opt, x;
	scanf("%d", &n);
	static int root[N];
	root[0] = wblt._new((1ll<<31) - 1);
	wblt.lp(root[0]) = wblt._new(-(1ll<<31) + 1);
	wblt.rp(root[0]) = wblt._new((1ll<<31) - 1);
	wblt.nodes[1].siz = 2;
	wblt.prt(root[0]);
	
	for (int id(1); id <= n; ++id) {
		scanf("%d %d %d", &vi, &opt, &x);
		printf("\nProc ID %d (%d %d %d)\n", id, vi, opt, x);
		root[id] = root[vi];
		switch(opt) {
			case 1: // insert
				wblt.insert(root[id] = 0, root[vi], x);
				break;
			case 2: // remove
				wblt.remove(root[id] = 0, root[vi], x);
				break;
			case 3: // rank x
				printf("%d\n", wblt.count(root[vi], x));
				break;
			case 4: // kth x
				printf("%d\n", wblt.kth(root[vi], x + 1));
				break;
			case 5: // pre x
				printf("%d\n", wblt.getpre(root[vi], x));
				break;
			case 6: // post x
				printf("%d\n", wblt.getpost(root[vi], x));
				break;
		}
		wblt.prt(root[id]);
	}
}