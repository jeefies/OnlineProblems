#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>

const int N = 5e5 + 7;

typedef unsigned long long data;

template<typename T>
T readI() {
	T x = 0, f = 1; char tmp;
	do {
		if ((tmp = getchar()) == '-') f = -1;
	} while (tmp < '0' || '9' < tmp);
	do {
		x = x * 10 + tmp - '0', tmp = getchar();
	} while ('0' <= tmp && tmp <= '9');
	return x * f;
}

data max(const data &a, const data &b) {
	return a > b ? a : b;
}

int n;
data A[N], B[N];

struct Ques {
	int l, i;
};
int qn;
std::deque<Ques> q[N];

void read() {
	readI<int>();
	// scanf("%d %d", &t, &n);
	n = readI<int>();
	
	for (int i = 1; i <= n; ++i) {
		A[i] = readI<data>();
		// scanf("%llu", A + i);
	}
	for (int i = 1; i <= n; ++i) {
		B[i] = readI<data>();
		// scanf("%llu", B + i);
	}
	
	qn = readI<int>();
	int l, r;
	for (int i = 1; i <= qn; ++i) {
		l = readI<int>(), r = readI<int>();
		q[r].push_back({l, i});
	}
}

static data res[N];
void proc() {
	static data a[N], b[N], f[N];
	for (int r = 1; r <= n; ++r) {
		for (int k = 1; k <= r; ++k) {
			a[k] = max(a[k], A[r]);
			b[k] = max(b[k], B[r]);
			f[k] += a[k] * b[k];
		}
		
		int i;
		for (auto qs : q[r]) {
			i = qs.i;
			for (int k = qs.l; k <= r; ++k) res[i] += f[k];
		}
	}
}

void output() {
	for (int i = 1; i <= qn; ++i) {
		printf("%llu\n", res[i]);
	}
}

int main() {
	read();
	proc();
	output();
	return 0;
}