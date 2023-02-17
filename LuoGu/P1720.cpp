#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 10000;

typedef vector<long long> vec;
typedef vector<vec> mat;

// res save to a
void mul(mat &ma, mat &mb) {
	long long a = ma[0][0], b = ma[0][1], c = ma[1][0], d = ma[1][1];
	long long x = mb[0][0], y = mb[0][1], z = mb[1][0], w = mb[1][1];
	ma[0][0] = (a * x + b * z) % MOD;
	ma[0][1] = (a * y + b * w) % MOD;
	ma[1][0] = (a * c + d * z) % MOD;
	ma[1][1] = (c * y + d * w) % MOD;
}

int main() {
	int n;
	mat res(2, vec(2, 0)), fib(2, vec(2, 0));
	while (cin >> n && ~n) {
		if (n <= 2) {
			cout << (n ? 1 : 0) << endl; continue;
		}
		res[0][0] = res[1][1] = 1;
		res[0][1] = res[1][0] = 0;
		fib[0][0] = fib[0][1] = fib[1][0] = 1;
		fib[1][1] = 1;
		// for (int i = 0; i < n - 1; ++i) {
		// 	mul(res, fib);
		// }
		n -= 1;
		// time n - 1
		while (n) {
			if (n & 1) mul(res, fib);
			mul(fib, fib), n >>= 1;
		}
		// printMat(res);
		cout << res[0][0] << endl;
	}
	return 0;	
}