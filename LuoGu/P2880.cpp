#include <cstdio>

const int N = 5e4 + 2;

int n, q;
int Log2[N];

template<typename T>
class STable {
public:
	typedef T(*OP_FUNC)(const T, const T);
	OP_FUNC op;
	T table[N + 1][17];
	//  fk is short for function
	void preset(T (*fk)(T, T)) {
		op = fk;
	}
	void init(T *a, int n) {
		for (int i = 1; i <= n; ++i) table[i][0] = a[i];
		
		int t = Log2[n];
		for (int k = 1; k <= t; ++k) {
			for (int i = 1; i + (1<<k) - 1 <= n; ++i)
				table[i][k] = op(table[i][k-1], table[i+(1<<(k-1))][k-1]);
		}
	}
	T query(int l, int r) {
		int k = Log2[r - l + 1];
		return op(table[l][k], table[r - (1<<k) + 1][k]);
	}
};

inline int max(int a, int b) {
	return a > b ? a : b;
}

inline int min(int a, int b) {
	return a < b ? a : b; 
} 

int a[N];
STable<int> big, small;
int main() {
	scanf("%d %d", &n, &q); 
	for (int i = 2; i <= n; i++) Log2[i] = Log2[i>>1] + 1;
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	big.preset(max), small.preset(min);
	big.init(a, n), small.init(a, n);
	
	int l, r;
	for (int i = 1; i <= q; ++i) {
		scanf("%d %d", &l, &r);
		printf("%d\n", big.query(l, r) - small.query(l, r));
	}
	
	return 0;
}
