#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int readInt() {
	char tmp; int x = 0, f = 1;
	do { if ((tmp = getchar()) == '-') f = -1; } while (tmp < '0' || tmp > '9');
	do { x = x * 10 + tmp - '0', tmp = getchar(); } while ('0' <= tmp && tmp <= '9');
	return x * f;
}

const int N = 2e5 + 7;

struct Line {
	int l, r, h, f;
	bool operator < (const Line & li) {
		return h < li.h;
	}
};

#define RI(v) v = readInt()

int n;
int x1[N], Y1[N], x2[N], Y2[N];
int xmap[N * 2];
Line lines[N * 2];
int ln, xn;
void read() {
	n = readInt(), ln = n * 2;
	
	int a, b, c, d; // x a c, y b d
	for (int i = 1; i <= n; ++i) {
		RI(x1[i]), RI(Y1[i]), RI(x2[i]), RI(Y2[i]);
		xmap[i * 2 - 1] = x1[i], xmap[i * 2] = x2[i];
	}
	
	// damn it discrete
	sort(xmap + 1, xmap + 1 + ln);
	int * end = unique(xmap + 1, xmap + 1 + ln);
	xn = end - xmap - 1;
	for (int i = 1; i <= n; ++i) {
		x1[i] = lower_bound(xmap + 1, end, x1[i]) - xmap;
		x2[i] = lower_bound(xmap + 1, end, x2[i]) - xmap;
	}
	
	for (int i = 1; i <= n; ++i) {
		lines[i * 2] = {x1[i], x2[i], Y2[i], -1};
		lines[i * 2 - 1] = {x1[i], x2[i], Y1[i], 1};
	}
	
	sort(lines + 1, lines + 1 + ln);
}

typedef long long data;
namespace seg {
	struct SegTree {
		int l, r;
		// cnt, area length
		// sum, completely cover times
		data cnt, sum, len;
		SegTree() {
			sum = cnt = 0;
		}
	};
	SegTree tree[N * 8];
	
	#define lp (p*2)
	#define rp (p*2+1)
	#define ct tree[p]
	#define lt tree[lp]
	#define rt tree[rp]
	
	inline void build(int p, int l, int r) {
		ct.l = l, ct.r = r;
		if (l == r) {
			ct.len = xmap[r + 1] - xmap[l];
			return;
		}
		
		int mid = (l + r) >> 1;
		build(lp, l, mid), build(rp, mid + 1, r);
		ct.len = lt.len + rt.len;
	}
	
	void init(int n) {
		build(1, 1, n);
	}
	
	inline void update(int p) {
		// ct.cnt = ct.sum == 0 ? lt.cnt + rt.cnt : ct.len;
		if (ct.sum) ct.cnt = ct.len;
		else ct.cnt = lt.cnt + rt.cnt;
	}
	
	inline void change(int p, int l, int r, const data & val) {
		if (l <= ct.l && ct.r <= r) {
			ct.sum += val;
			update(p);
			return;
		}
		
		if (l <= lt.r) change(lp, l, r, val);
		if (rt.l <= r) change(rp, l, r, val);
		update(p);
	}
	
	void change(int l, int r, const data & val) {
		// printf("In changing [%d, %d] (val = %d)\n", l, r, val);
		change(1, l, r, val);
	}
}

#define iL lines[i]
#define il iL.l
#define ir iL.r
#define ih iL.h
#define rh (lines[i + 1].h - ih)
int main() {
	read();
	/*
	printf("Read xn = %d\n", xn);
	for (int i = 1; i <= xn; ++i) {
		printf("Xmap[%d] = %d\n", i, xmap[i]);
	}
	
	for (int i = 1; i <= ln; ++i) {
		printf("Line {%d, %d, %d, %d} xmap to [%d, %d]\n", il, ir, ih, iL.f, xmap[il], xmap[ir]);
	}
	*/
	seg::init(xn - 1);
	
	data tot = 0;
	for (int i = 1; i < ln; ++i) {
		// cover [il, ir - 1]
		if (il < ir) seg::change(il, ir - 1, iL.f);
		// printf("tot from %d ", tot);
		// tot += seg::query(0, xn) * rh;
		tot += seg::tree[1].cnt * rh;
		// printf("add to %d\n", tot);
	}
	printf("%lld\n", tot);
	return 0;
}