#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

template<typename T, typename Num>
inline T qpow(T a, Num x, Num p) {
	T r(1);
	while (x) {
		if (x & 1) r = (a * r) % p;
		a = (a * a) % p, x >>= 1;
	}
	return r;
}

typedef long long data;

data p, i2;

class exNum {
public:
	data a, b;
	exNum(data a) : a(a % p), b(0) { };
	exNum(data a, data b) : a(a % p), b(b % p) { }
	inline exNum operator * (const exNum & e) const {
		exNum c(a * e.a % p + b * e.b % p * i2, b * e.a + a * e.b); 
		return c;
	}
	
	inline exNum operator % (const data &mod) const {
		return exNum(a % mod, b % mod);
	}
};

inline data legendre(data a) {
	a = (a % p + p) % p;
	return qpow(a, (p - 1) / 2, p);
}

inline data findA(data n) {
	for (data a = 1; a < p; ++a) {
		if (legendre(a * a - n) == p - 1) return a;
	}
	return -1;
}

inline data Cipolla(data n) {
	// cout << "Cipolla: " << n << endl;
	n %= p;
	// printf("Legendre(%lld, %lld) = %lld\n", n, p, legendre(n));
	if (legendre(n) != 1) return -1;
	data a = findA(n);
	i2 = a * a - n;
	// cout << "I2: " << i2 << endl;
	// cout << "findA: " << a << endl;
	exNum en(a, 1);
	en = qpow(en, (p + 1) / 2, p);
	if (en.a < 0) return en.a + p;
	return en.a;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	int T;
	cin >> T;
	
	data n;
	while (T--) {
		cin >> n >> p;
		if (!n || n % p == 0) {
			cout << "0\n";
			continue;
		}
		data res = Cipolla(n);
		if (res == -1) {
			cout << "Hola!\n";
		} else {
			data res2 = -res + p;
			if (res2 < res) swap(res, res2);
			if (res2 ^ res) cout << res << ' ' << res2 << '\n';
			else cout << res << '\n';
		}
	}
	return 0;
}