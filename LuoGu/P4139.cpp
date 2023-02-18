#include <iostream>
#include <algorithm>

using namespace std;
const int N = 1e7 + 7;

int primes[N], notp[N], pc(0), phi[N];

template<typename T, typename X, typename P>
T qpow(T a, X x, P p) {
	a %= p;
	T r(1);
	while (x) {
		if (x & 1) r = (long long)r * a % p;
		a = (long long)a * a % p, x >>= 1;
	}
	return r;
}

void getPrimes() {
	phi[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!notp[i]) {
			primes[pc++] = i, phi[i] = i - 1;
		}
		for (int k(0), j; k < pc && (j = i * primes[k]) < N; ++k) {
			notp[j] = 1;
			if (i % primes[k] == 0) {
				phi[j] = phi[i] * primes[k];
				break;
			} else {
				phi[j] = phi[i] * phi[primes[k]];
			}
		}
	}
}

void proc() {
	int p;
	scanf("%d", &p);

	const int varphi(phi[p]);

	int a(1), next;
	do {
		next = qpow(2, a, p);
	} while (a != next);
	printf("%d\n", a);
}

int main() {
	getPrimes();

	int T;
	scanf("%d",&T);

	while (T--) {
		proc();
	}

	return 0;
}
