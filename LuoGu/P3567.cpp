#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

using std::cout;

template<typename T>
inline void read(T &x) {
	char c, f(0); x = 0;
	do if ((c = getchar()) == '-') f = true; while (isspace(c));
	do x = (x<<3) + (x<<1) + (c ^ 48), c = getchar(); while (isdigit(c));
	if (f) x = -x;
}
template <typename T, typename ...Args> inline void read(T &t, Args&... args) { read(t), read(args...); }

typedef unsigned int uint;
const int N = 5e5 + 7;

uint n;
uint a[N];

namespace SG {
	struct Node {
		uint l, r, cnt;
	} tr[N * 20];
	
	uint siz = 0;
	uint root[N];
	
	#define cnt(p) tr[p].cnt
	#define lp(p) tr[p].l
	#define rp(p) tr[p].r
	
	inline void update(uint &p, uint q, uint l, uint r, uint x) {
		if (!p) p = ++siz, cnt(p) = cnt(q);
		
		if (l == r) {
			++cnt(p);
			return;
		}
		
		uint mid = (l + r) >> 1;
		if (x <= mid) {
			rp(p) = rp(q);
			update(lp(p), lp(q), l, mid, x);
		} else {
			lp(p) = lp(q);
			update(rp(p), rp(q), mid + 1, r, x);
		}
		cnt(p) = cnt(lp(p)) + cnt(rp(p));
		// cout << '[' << l << ", " << r << "] count " << cnt(p) << std::endl;
	}
	
	void init() {
		for (uint i = 1; i <= n; ++i)
			update(root[i] = 0, root[i - 1], 1, n, a[i]);
	}
	
	inline uint kth(uint p, uint q, uint l, uint r, uint k) {
		if (l == r) return l;
		
		// not enough elements
		// if (cnt(q) - cnt(p) <= k) return 0;
		
		uint mid = (l + r) >> 1, ls = cnt(lp(q)) - cnt(lp(p)), rs = cnt(rp(q)) - cnt(rp(p));
		// cout << "[" << l << ", " << r << "] ls, rs = " << ls << ',' << rs << std::endl;
		if (ls > k) return kth(lp(p), lp(q), l, mid, k);
		else if (rs > k) return kth(rp(p), rp(q), mid + 1, r, k);
		return 0;
	}
	
	uint kth(uint l, uint r, uint k) {
		return kth(root[l - 1], root[r], 1, n, k);
	}
}

int main() {
	uint q;
	read(n, q);
	
	for (uint i = 1; i <= n; ++i) {
		read(a[i]);
	} SG::init();
	
	uint l, r;
	for (uint i = 0; i ^ q; ++i) {
		read(l, r);
		cout << SG::kth(l, r, (r - l + 1) >> 1) << '\n';
	}
	cout.flush();
	return 0;
}