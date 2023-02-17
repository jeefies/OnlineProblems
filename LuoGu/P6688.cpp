#include <iostream>
#include <cstring>
#include <algorithm>

using std::min;
const int N = 1e6 + 7;

typedef unsigned int uint;
uint n, a[N];

namespace seg {
	uint pow[N], base(3);
	
	struct node {
		uint sum, minn;
		inline void merge(node n) {
			sum += n.sum;
			if (minn > n.minn) minn = n.minn;
		}
		void output(bool newline = false) {
			printf("(%u, %u)", sum, minn);
			if (newline) puts("");
		}
	} nodes[N * 4];
	
	#define lp(p) (p<<1)
	#define rp(p) (lp(p)|1)
	#define sum(p) nodes[p].sum
	#define minn(p) nodes[p].minn
	constexpr void init() {
		pow[0] = 1;
		for (uint i(1); i < N; ++i) pow[i] = pow[i - 1] * base; // natural overflow
	}
	
	inline void update(uint p) {
		minn(p) = min(minn(lp(p)), minn(rp(p)));
		sum(p) = sum(lp(p)) + sum(rp(p));
	}
	
	inline void build(uint p, uint l, uint r) {
		if (l == r) {
			return nodes[p] = {pow[a[l]], a[l]}, (void)0;
		}
		
		uint mid = (l + r) >> 1;
		build(lp(p), l, mid), build(rp(p), mid + 1, r);
		update(p);
	}
	void build() { build(1, 1, n); }
	
	inline node query(uint p, uint cl, uint cr, uint l, uint r) {
		// printf("In node %u, [%u, %u] (query [%u, %u])\n", p, cl, cr, l, r);
		if (l <= cl && cr <= r) return nodes[p];
		
		uint mid = (cl + cr) >> 1;
		node tmp = {0, 0x7F7F7F7F};
		if (l <= mid) tmp = query(lp(p), cl, mid, l, r);
		if (mid < r) tmp.merge(query(rp(p), mid + 1, cr, l, r));
		// printf("Node %u get ", p), tmp.output(true);
		return tmp;
	}
	node query(uint l, uint r) { return query(1, 1, n, l, r); }
	
	inline void change(uint p, uint cl, uint cr, uint i, uint v) {
		if (cl == cr) {
			return nodes[p] = {pow[v], v}, (void)0;
		}
		
		uint mid = (cl + cr) >> 1;
		if (i <= mid) change(lp(p), cl, mid, i, v);
		else change(rp(p), mid + 1, cr, i, v);
		update(p);
	}
	void change(uint i, uint v) { change(1, 1, n, i, v); }
}

int main() {
	uint q;
	scanf("%u %u", &n, &q);
	for (int i = 1; i <= n; ++i) scanf("%u", a + i);
	seg::init();
	seg::build();
	
	uint op, x, y, l, r;
	while (q--) {
		scanf("%u %u %u", &op, &x, &y);
		if (op == 0) {
			seg::change(x, y);
		} else {
			scanf("%u %u", &l, &r);
			seg::node a = seg::query(x, y), b = seg::query(l, r);
			if (a.minn > b.minn) std::swap(a, b);
			if (a.sum * seg::pow[b.minn - a.minn] == b.sum) {
				puts("YES");
			} else {
				puts("NO");
			}
		}
	}
	return 0;
}