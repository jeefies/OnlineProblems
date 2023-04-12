#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
const int N = 1e5 + 7;

// uint define for index!
typedef unsigned int uint;

// left leaning tree!
// like a heap, like a merge_find_set, like a treap! (TMD)
struct LTree {
	int val;
	int dis; // this make's it differ from heap!
	uint lp, rp, fa;
	LTree() : dis(-1) {}
};

LTree tree[N];
#define lp(p) tree[p].lp
#define rp(p) tree[p].rp
#define fa(p) tree[p].fa
#define dis(p) tree[p].dis
#define val(p) tree[p].val

uint merge(uint x, uint y) {
	if (!x | !y) return x | y; // return none empty! (learning from a DaLao!)
	if (val(x) > val(y)) swap(x, y); // make sure val(x) \le val(y) (A Heap!)
	rp(x) = merge(rp(x), y); // merge left or x and y!
	if (dis(rp(x)) > dis(lp(x))) swap(rp(x), lp(x)); // make sure dis(lp(x)) >= dis(rp(x)) (Left Leaning!)
	dis(x) = dis(rp(x)) + 1; // update dis!
	fa(x) = fa(rp(x)) = fa(lp(x)) = x; // update father (A MergeFindSet!)
	return x;
}

// in this problem (https://www.luogu.com.cn/problem/P3377) we don't need to mark it removed!
// we just need to make it's val to -1 and output is ok
void remove(uint x) {
	val(x) = -1, fa(rp(x)) = rp(x),fa(lp(x)) = lp(x);
	fa(x) = merge(lp(x), rp(x)); // why we need this! for we use path shorten in searching for top!
}

uint find(uint x) {
	if (fa(x) == x) return x;
	return fa(x) = find(fa(x));
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	// read val
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &val(i)), fa(i) = i;
	}
	
	int op;
	uint x, y;
	for (int i = 1; i <= m; ++i) {
		scanf("%d ", &op);
		if (op & 1) { // op == 1
			scanf("%u %u", &x, &y);
			if (val(x) == -1 || val(y) == -1) continue;
			uint fx = find(x), fy = find(y);
			if (fx ^ fy) fa(fx) = fa(fy) = merge(fx, fy);
		} else {
			scanf("%u", &x);
			if (val(x) == -1) puts("-1");
			else printf("%d\n", val(find(x))), remove(find(x));
		}
	}
	return 0;
}