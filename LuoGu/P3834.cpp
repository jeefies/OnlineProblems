#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 2e5 + 7;
static int n, a[N], ori[N];

namespace SG {
	struct Node {
		int ltp, rtp, cnt;
	};
	Node tree[N * 42];
	int rts[N], siz = 0;
	
	#define cnt(p) tree[p].cnt
	#define lp(p) tree[p].ltp
	#define rp(p) tree[p].rtp
	#define lt(p) tree[lp(p)]
	#define rt(p) tree[rp(p)]
	
	inline void zero(int & p, int l = 1, int r = n) {
		if (!p) p = ++siz;
		if (l ^ r) {
			int mid = (l + r) >> 1;
			zero(lp(p), l, mid), zero(rp(p), mid + 1, r);
		} // else l == r, nothing to do when build. we just need a plain tree
		else tree[p] = {0, 0, 0};
	}
	
	// copy p to t
	inline void update(int & t, int p, int x, int l = 1, int r = n) {
		if (!t) t = ++siz, cnt(t) = cnt(p), cnt(t) = cnt(p);
		
		if (l == r) {
			++cnt(t);
			return;
		}
		
		int mid = (l + r) >> 1;
		if (x <= mid) {
			rp(t) = rp(p);
			update(lp(t), lp(p), x, l, mid);
		} else {
			lp(t) = lp(p);
			update(rp(t), rp(p), x, mid + 1, r);
		}
		cnt(t) = cnt(lp(t)) + cnt(rp(t)); // pushup
		// cout << '[' << l << ", " << r << "] count " << cnt(t) << endl;
	}
	
	void init() {
		zero(rts[0]);
		for (int i = 1; i <= n; ++i) {
			// cout << "In merging " << i << endl;
			update(rts[i] = 0, rts[i - 1], a[i]);
		}
	}
	
	inline int kth(int p, int q, int k, int l, int r) {
		// cout << "In searching [" << l << ", " << r << "] k = " << k << endl;
		if (l == r) return ori[l];
		
		int mid = (l + r) >> 1, leftCount = cnt(lp(q)) - cnt(lp(p));
		if (leftCount >= k) {
			// cout << "In left:" << endl;
			// left cnt bigger than k
			return kth(lp(p), lp(q), k, l, mid);
		} else {
			// cout << "In right:" << endl;
			return kth(rp(p), rp(q), k - leftCount, mid + 1, r);
		}
	}
	
	int kth(int l, int r, int k) {
		return kth(rts[l - 1], rts[r], k, 1, n);
	}
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	
	int T;
	cin >> n >> T;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; ori[i] = a[i];
 	}
 	
 	int *bstart = ori + 1, *bend = ori + 1 + n;
	sort(bstart, bend);
	bend = unique(bstart, bend);
 	for (int i = 1; i <= n; ++i) {
 		a[i] = lower_bound(bstart, bend, a[i]) - ori;
	 }
	 
	 SG::init();
	 
	 int l, r, k;
	 while (T--) {
	 	cin >> l >> r >> k;
	 	cout << SG::kth(l, r, k) << endl;
	 }
	 return 0;
}