#include <iostream>
#include <algorithm>

using namespace std;

typedef long long jint;

struct Equation {
	jint a, p;
};

template<typename T>
T gcd(T a, T b) {
	return b ? gcd(b, a % b) : a;
}

template<typename T>
T exgcd(T a, T b, T &x, T &y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}

	int t = exgcd(b, a % b, y, x);
	y -= (a / b) * x;
	return t;
}

Equation merge(const Equation &x, const Equation &y) {
	jint c = (y.a - x.a) % y.p;
	if (c < 0) c += y.p;

	// k1 x.p + k2 y.p = c
	jint d = gcd(x.p, y.p), k1, k2;
	exgcd(x.p / d, y.p / d, k1, k2);

	if (c % d) cout << "Failed\n"; // failed

	// find least positive k1
	k1 = k1 * (c / d) % y.p;
	if (k1 < 0) k1 += y.p;

	jint lcm = x.p / d * y.p;
	Equation r = {(x.a + k1 * x.p % lcm) % lcm, lcm};
	if (r.a < 0) r.a += lcm;
	return r;
}

int main() {
	int n;
	scanf("%d", &n);

	int a, p;
	scanf("%d %d", &p, &a);
	Equation e = {a, p};
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &p, &a);
		e = merge(e, {a, p});
	}
	cout << e.a;
	return 0;
}
