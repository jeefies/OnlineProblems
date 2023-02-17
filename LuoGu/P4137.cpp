#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

template<typename T>
inline void read(T &x) {
	char c, f(0); x = 0;
	do if ((c = getchar()) == '-') f = true; while (isspace(c));
	do x = (x<<3) + (x<<1) + (c ^ 48), c = getchar(); while (isdigit(c));
	if (f) x = -x;
}
template <typename T, typename ...Args> inline void read(T &t, Args&... args) { read(t), read(args...); }

using namespace std;
const int N = 2e5 + 7, B = 512;

int n, m, nq;
int but[N], a[N], mex = 0;
// block number count, for jumping mex
// [k*B, (k+1)*B)
int bbut[N]; 

inline void add(int ap) {
	if (but[ap]++ == 0) ++bbut[ap / B];
}

inline void del(int ap) {
	if (--but[ap] == 0) --bbut[ap / B];
}

struct Ques {
	int l, r, i;
	bool operator < (const Ques & q) {
		if (l / nq ^ q.l / nq) return l < q.l;
		if (l / nq & 1) return r > q.r;
		return r < q.r;
	}
} ques[N];

int res[N];
int main() {
	read(n, m);
	nq = B;
	for (int i = 1; i <= n; ++i) read(a[i]);
	
	Ques * qptr = ques;
	for (int i = 1; i <= m; ++i) {
		++qptr; qptr->i = i;
		read(qptr->l, qptr->r);
	}
	sort(ques + 1, qptr + 1);
	
	qptr = ques;
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i) {
		++qptr;
		// printf("{%d %d %d}\n", qptr->l, qptr->r, qptr->i);
		while (r < qptr->r) add(a[++r]);
		while (r > qptr->r) del(a[r--]);
		while (l > qptr->l) add(a[--l]);
		while (l < qptr->l) del(a[l++]);
		
		int k = 0;
		while (bbut[k] == B) ++k; // all number exists in block k.
		// searching in block k.
		k = k * B + B;
		for (int i = k - B; i < k; ++i) {
			if (but[i] == 0) mex = i, i = k;
		}
		res[qptr->i] = mex;
	}
	
	for (int i = 1; i <= m; ++i) {
		cout << res[i] << '\n';
	}
	cout.flush();
	return 0;
}