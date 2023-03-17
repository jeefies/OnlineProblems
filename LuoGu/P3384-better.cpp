#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;
const int N = 2e5 + 7;

static int n;
int a[N], ori[N], rts[N];

class SegTree {
private:
	int lc[N * 42], rc[N * 42], cnt[N * 42];
	int usage;
public:
	SegTree() : usage(0) {}
	
	void build(int & p, int l = 1, int r = n) {
		if (!p) p = ++usage;
		if (l ^ r) {
			int mid = (l + r) >> 1;
			build(lc[p], l, mid), build(rc[p], mid + 1, r);
		} else lc[p] = rc[p] = cnt[p] = 0;
	}
	
	void update(int & t, int p, int x, int l = 1, int r = n) {
		if (!t) 
			t = ++usage, cnt[t] = cnt[p];
		
		if (l == r) {
			++cnt[t];
			return;
		}
		
		int mid = (l + r) >> 1;
		if (x <= mid) {
			rc[t] = rc[p];
			update(lc[t], lc[p], x, l, mid);
		} else {
			lc[t] = lc[p];
			update(rc[t], rc[p], x, mid + 1, r);
		}
		cnt[t] = cnt[lc[t]] + cnt[rc[t]];
	}
	
	int kth(int p, int q, int k, int l = 1, int r = n) {
		if (l == r) return ori[l];
		
		int mid = (l + r) >> 1, leftCount = cnt[lc[q]] - cnt[lc[p]];
		if (leftCount >= k)
			return kth(lc[p], lc[q], k, l, mid);
		return kth(rc[p], rc[q], k - leftCount, mid + 1, r);
	}
} tree;

int main() {
	cin.tie(0)->sync_with_stdio(false);
	 
	int q;
	cin >> n >> q;
	
	for (int i = 1; i <= n; ++i)
		(cin >> a[i]), ori[i] = a[i];
	
	int *sptr = ori + 1, *eptr = ori + 1 + n;
	sort(sptr, eptr);
	eptr = unique(sptr, eptr);
	
	tree.build(rts[0]);
	for (int i = 1; i <= n; ++i) {
		tree.update(rts[i] = 0, rts[i - 1], lower_bound(sptr, eptr, a[i]) - ori);
	}
	
	for (int l, r, k, i = 1; i <= q; ++i) {
		cin >> l >> r >> k;
		cout << tree.kth(rts[l - 1], rts[r], k) << '\n';
	}
}