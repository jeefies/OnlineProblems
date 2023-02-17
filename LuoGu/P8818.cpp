#include <iostream>

const int INF = 1e9 + 7, N = 1e5 + 7;

class Log2Factory {
public:
	int lg2[N];
	Log2Factory() {
		for (int i = 2; i < N; ++i) lg2[i] = lg2[i>>1] + 1;
	}
	int operator() (int i) const {
		return lg2[i];
	}
};

Log2Factory Log2;

class STable {
public:
	int (*op)(int, int);
	int f[N][20];
	
	void init(int * a, int n) {
		for (int i = 1; i <= n; ++i) {
			f[i][0] = a[i];
		}
		
		int t = Log2(n);
		for (int k = 1; k <= t; ++k) {
			for (int i = 1; i + (1<<k) - 1 <= n; ++i) {
				f[i][k] = op(f[i][k-1], f[i + (1 << (k-1))][k-1]);
			}
		}
	}
	
	int query(int l, int r) {
		int k = Log2(r - l + 1);
		return op(f[l][k], f[r-(1<<k)+1][k]);
	}
};

inline int max(int a, int b) {
	return a > b ? a : b;
}

inline long long lmax(long long a, long long b) {
	return a > b ? a : b;
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

static STable Amax, Amin, Anmax, Bmin, Bmax;
inline void proc() {
	static int l1, r1, l2, r2;
	scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
	
	long long ans = -1ll * INF * INF; // make ans least
	
	/*
	4 situations:
	1. + -
	2. + +
	3. - +
	4. - -
	*/
	
	// sit 1, 2
	int a = Amax.query(l1, r1);
	if (a > 0) ans = 1ll * a * Bmin.query(l2, r2);
	
	printf("sit 1, 2 get ans %lld\n", ans);
	
	// sit 3
	a = Anmax.query(l1, r1);
	int b = Bmax.query(l2, r2);
	if (b > 0 && a != -INF) ans = lmax(ans, 1ll * a * b);
	
	printf("sit 3 get ans %lld\n", ans);
	
	// sit 4
	a = Amin.query(l1, r1);
	b = Bmin.query(l2, r2);
	if (a < 0 && b < 0) ans = lmax(ans, 1ll * a * b);
		
	printf("%lld\n", ans);
}

int n, m, q;
int A[N], A2[N], B[N];
int main() {
	scanf("%d %d %d", &n, &m, &q);
	
	int t;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &t);
		A[i] = t, A2[i] = t < 0 ? t : -INF;
	}
	
	for (int i = 1; i <= m; ++i) {
		scanf("%d", B + i);
	}
	
	Amax.op = Bmax.op = Anmax.op = max;
	Amin.op = Bmin.op = min;
	
	Amax.init(A, n), Anmax.init(A2, n), Amin.init(A, n);
	Bmin.init(B, m), Bmax.init(B, m);
	
	while (q--) {
		proc();
	}
}