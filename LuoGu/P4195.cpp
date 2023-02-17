#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

template<typename T>
inline void read(T &x) {
	char c, f(0); x = 0;
	do if ((c = getchar()) == '-') f = true; while (isspace(c));
	do x = (x<<3) + (x<<1) + (c ^ 48), c = getchar(); while (isdigit(c));
	if (f) x = -x;
}
template <typename T, typename ...Args> inline void read(T &t, Args&... args) { read(t), read(args...); }

template<typename T>
T gcd(T x, T y) {
	T c;
	while (y)
		c = x % y, x = y, y = c;
	return x;
}

template<typename T>
T exgcd(T a, T b, T *s, T *t) {
    if (b == 0) {
        *s = 1, *t = 0;
        return a;
    }
    T r = exgcd(b, a % b, t, s);
    *t -= (a / b) * *s;
    return r;
}

// inv(i) i \equiv 1 mod p
// i * inv(i) + kp = 1 (kown i, p, 1)
template<typename T>
T inv(T i, T p) {
	T iv, k;
	exgcd(i, p, &iv, &k), iv %= p;
	return iv < 0 ? iv + p : iv;
}

template<typename T>
T qpow(T a, T b, T p) {
	T r(1);
	while (b) {
		if (b & 1) r = (r * a) % p;
		a = (a * a) % p, b >>= 1;
	}
	return r;
}

typedef long long data;

template<typename data>
data BSGS(data a, data b, data p) {
	b %= p;
	static std::map<data, data> hash; hash.clear();
	// t ceil
	data t = std::ceil(std::sqrt(p)), v(1), j(0);
	
	for (; j < t; ++j) {
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

data exBSGS(data a, data b, data p) {
	a %= p, b %= p;
	// a^0 = 1, a^k = 0 mod p
	if (b == 1 || p == 1) return 0;
	// d for gcd, ak for a^k / D
	data d, ak(1), k(0);
	while ((d = gcd(a, p)) != 1) {
		if (b % d) return -1;
		++k, p /= d, b /= d;
		ak = a / d * ak % p;
		if (ak == b) return k;
	}
	
	// a^k/D * a^res \equiv b / D mod p / D
	// a^res \equiv b / D * inv(a^k/D) mod p/D
	// if gcd(a, p) == 1, b = b * inv(1 / 1) % p = b % p;
	// means it's normal BSGS algorithm
	b = b * inv(ak, p) % p;
	
	data res = BSGS(a, b, p);
	if (~res) return res + k;
	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	data a, b, p;
	while (cin >> a >> p >> b) {
		if ((a | b | p) == 0) break;
		data x = exBSGS(a, b, p);
		if (~x) cout << x << '\n';
		else cout << "No Solution\n";
	}
	return 0;
}