#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

inline ll gcd(ll a, ll b) {
	ll t;
	while (b) {
		t = b, b = a % b, a = t;
	}
	return a;
}

inline ll exgcd(ll a, ll b, ll &s, ll &t) {
	if (b == 0) {
		s = 1, t = 0;
		return a;
	}
	
	ll r = exgcd(b, a % b, t, s);
	t -= (a / b) * s;
	return r;
}

inline ll mul(ll a, ll b, ll mod) {
	return (__int128)a % mod * b % mod;
	
	ll r(0);
	while (b) {
		if (b & 1) r = (r + a) % mod;
		a = (a + a) % mod, b >>= 1;
	}
	return r;
}

inline void merge(ll & a1, ll & m1) {
	ll a2, m2;
	scanf("%lld %lld", &m2, &a2);
	
	ll c = (a2 - a1) % m2;
	if (c < 0) c += m2;
	
	ll d = gcd(m1, m2), s, t;
	exgcd(m1 / d, m2 / d, s, t);
	// get right solution to $s m_1 + t _m2 = c$
	s = mul(s, c / d, m2);
	if (s < 0) s += m2;
	
	ll lcm = m1 / d * m2;
	
	a1 = (a1 + mul(s, m1, lcm)) % lcm;
	if (a1 < 0) a1 += lcm;
	m1 = lcm;
}

int main() {
	int n;
	scanf("%d", &n);
	
	ll a1, m1;
	scanf("%lld %lld", &m1, &a1);
	
	for (int i = 1; i < n; ++i) {
		merge(a1, m1);
	}
	
	printf("%lld\n", a1);
	return 0;
}