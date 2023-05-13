#include <iostream>
#include <algorithm>
#include <cstdint>
#include <stack>

using namespace std;

#define BS 30

// Maybe MLE!!!
template<int N = (int)2e6 + 2>
class BSTrie {
private:
	int16_t siz[N << 5];
	int ch[N << 5][2];
	int usage;
	stack<int> wasted;
public:
	#define bit(x, i) ((x >> i) & 1)
	#define newNode() ({ \
		int cur; if (wasted.empty()) cur = ++usage; else cur = wasted.top(), wasted.pop(); \
		siz[cur] = ch[cur][0] = ch[cur][1] = 0; \
		cur; \
	})
	
	BSTrie() : usage(0) {
		newNode(); // neg root 1
		newNode(); // pos root 2
	}
	void insert(int x) {
//		clog << "Ins " << x << '\n';
		int p = x < 0 ? 1 : 2;
		for (int i = BS; ~i; --i) {
			int bt = bit(x, i), &np = ch[p][bt];
			if (!np) np = newNode();
			++siz[p], p = np;
		} ++siz[p];
	}
	
	void remove(int x) {
		int p = x < 0 ? 1 : 2;
		for (int i = BS; ~i; --i) {
			int np = ch[p][bit(x, i)];
			if (!np) {
				return;
			} p = np;
		}
		
		p = x < 0 ? 1 : 2;
		--siz[p];
		for (int i = BS; ~i; --i) {
			int np = ch[p][bit(x, i)];
			if (--siz[np] == 0) wasted.push(np), ch[p][bit(x, i)] = 0;
			p = np;
		}
	}
	
	int rank(int x, bool within = false) {
		int p = x < 0 ? 1 : 2;
		int rk = 0;
		if (x >= 0) rk += siz[1];
		for (int i = BS; ~i; --i) {
			int bt = bit(x, i), np = ch[p][bt];
			if (bt) rk += siz[ch[p][0]];
			if (!np) return rk;
			p = np;
		}
		
		return within ? rk + siz[p] : rk;
	}
	
	#define lc(p) (ch[p][0])
	#define rc(p) (ch[p][1])
	#define NEGEMASK 0x80000000
	int kth(int k) {
		int p = k <= siz[1] ? 1 : 2;
		int x = k <= siz[1] ? (1 << (32 - BS)) - 1 : 0;
		for (int i = BS; ~i; --i) {
			if (k <= siz[lc(p)]) p = lc(p), x <<= 1;
			else k -= siz[lc(p)], p = rc(p), x = (x << 1) | 1;
		}
		return x;
	}
}; 
BSTrie<> bst;

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	int n;
	cin >> n;
	for (int op, x, i = 0; i < n; ++i) {
		cin >> op >> x;
		switch (op) {
			case 1: bst.insert(x); break;
			case 2: bst.remove(x); break;
			case 3: cout << bst.rank(x) + 1 << '\n'; break;
			case 4: cout << bst.kth(x) << '\n'; break;
			case 5: cout << bst.kth(bst.rank(x)) << '\n'; break;
			case 6: cout << bst.kth(bst.rank(x, true) + 1) << '\n'; break;
			default: clog << "Error!\n";
		}
	}
}

/*int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	int s, n, last = 0, ans = 0;
	cin >> s >> n;
	for (int x, i = 0; i < s; ++i) {
		cin >> x; bst.insert(x);
	}
	
	for (int op, x, i = 0; i < n; ++i) {
		cin >> op >> x; x ^= last;
		switch (op) {
			case 1: bst.insert(x); break;
			case 2: bst.remove(x); break;
			case 3: ans ^= last = bst.rank(x) + 1; break;
			case 4: ans ^= last = bst.kth(x); break;
			case 5: ans ^= last = bst.kth(bst.rank(x)); break;
			case 6: ans ^= last = bst.kth(bst.rank(x, true) + 1); break;
			default: clog << "Error!\n";
		}
	} cout << ans << '\n';
}*/
