#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

#define int long long

int qpow(int a, int x, int p) {
	if (x == 0) return 1 % p;
	int r = 1;
	while (x) {
		if (x & 1) r = (r * a) % p;
		a = (a * a) % p, x >>= 1;
	}
	return r;
}

int BSGS(int a, int b, int p) {
	map<int, int> hash; hash.clear();
	b %= p;
	int t = (int)sqrt(p) + 1;
	
	for (int j(0); j < t; ++j) {
		int v = b * qpow(a, j, p) % p;
		hash[v] = j;
	}
	
	a = qpow(a, t, p);
	if (a == 0) return b == 0 ? 1 : -1;
	
	for (int i(0); i <= t; ++i) {
		int v = qpow(a, i, p);
		int j = hash.find(v) == hash.end() ? -1 : hash[v];
		if (~j && i * t - j >= 0) return i * t - j;
	}
	return -1;
}

signed main() {
	int p, a, b;
	cin >> p >> a >> b;
	int l = BSGS(a, b, p);
	if (~l) cout << l;
	else cout << "no solution";
}