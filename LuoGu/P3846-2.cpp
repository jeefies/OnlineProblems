#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

#define TLL 1ll*

int qpow(int a, int b, int p) {
	int r = 1;
	while (b) {
		if (b & 1) r = (TLL r * a) % p;
		a = (TLL a * a) % p, b >>= 1;
	}
	return r;
}

// a^l \equiv b mod p
// a^(st) \equiv b*a^j mod p
template<typename data>
data BSGS(data a, data b, data p) {
	b %= p;
	data t = (data)sqrt(p), v(1), j(0);
	static map<data, data> hash; hash.clear();
	
	for (; j <= t; ++j) {
		hash[v * b % p] = j;
		v = v * a % p;
	}
	
	a = qpow(a, t, p), v = 1;
	/* 
	if a^t \equiv 0 mod p
	means a | p
	means \forall k a^k \equiv 0 mod p
	so it can work out a^l \equiv b mod p only if b == 0, or there's no solution
	*/
	if (a == 0) return b == 0 ? 1 : -1;
	
	// here a we already make it to a^t, so we only need ^s and find it.
	for (data s(0); s <= t; ++s) {
		j = hash.find(v) == hash.end() ? -1 : hash[v];
		if (~j && s * t >= j) return s * t - j;
		v = v * a % p;
	}
	return -1;
}

int main() {
	int p, a, b;
	cin >> p >> a >> b;
	int l = BSGS<long long>(a, b, p);
	if (~l) cout << l;
	else cout << "no solution";
	return 0;
}