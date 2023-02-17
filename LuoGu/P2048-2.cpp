#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

const int N = 5e5 + 7;

int n, k, L, R;
int prefix[N] = {0};

int readInt() {
	int n = 0, f = 1;
	char tmp;
	do {
		if ((tmp = getchar()) == '-') f = -1;
	} while (tmp < '0' || '9' < tmp);
	do {
		n = n * 10 + tmp - '0';
		tmp = getchar();
	} while ('0' <= tmp && tmp <= '9');
	return n * f;
}

void read() {
	scanf("%d %d %d %d", &n, &k, &L, &R);
	for (int i = 1; i <= n; ++i) {
		prefix[i] = readInt() + prefix[i - 1];
	}
}

namespace ST {
	int lg2[N];
	int st[N][21];
	
	inline int max(int a, int b) {
		return prefix[a] > prefix[b] ? a : b;
	}
	
	void init(int n) {
		st[1][0] = 1;
		for (int i = 2; i <= n; ++i)
			st[i][0] = i, lg2[i] = lg2[i>>1] + 1;
		
		int t = lg2[n];
		for (int k = 1; k <= t; ++k) {
			for (int i = 1; i + (1<<k) - 1 <= n; ++i)
				st[i][k] = max(st[i][k - 1], st[i + (1 << (k-1))][k - 1]);
		}
	}
	
	int query(int l, int r) {
		int k = lg2[r - l + 1];
		return max(st[l][k], st[r - (1<<k) + 1][k]);
	}
};

class Elem {
public:
	int i, l, r, val, t;
	Elem(int i_, int l_, int r_) : i(i_), l(l_), r(r_) {
		t = ST::query(l, r);
		val = prefix[t] - prefix[i - 1];
	}
	
	bool operator < (const Elem & e) const {
		return val < e.val;
	}
};

int main() {
	read();
	ST::init(n);
	
	std::priority_queue<Elem> que;
	for (int i = 1; i + L - 1 <= n; ++i) {
		if (i + R - 1 <= n) que.push(Elem(i, i + L - 1, i + R - 1));
		else que.push(Elem(i, i + L - 1, n));
	}
	long long ans = 0;
	while (k--) {
		Elem e = que.top(); que.pop();
		ans += e.val;
		// printf("Ans += %d to %lld (%d, %d, %d, %d)\n", e.val, ans, e.i, e.l, e.t, e.r);
		if (e.t > e.l) que.push(Elem(e.i, e.l, e.t - 1));
		if (e.t < e.r) que.push(Elem(e.i, e.t + 1, e.r));
	}
	printf("%lld\n", ans);
	return 0;
}