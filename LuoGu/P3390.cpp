#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const int MOD = 1e9 + 7;

typedef vector<long long> vec;
typedef vector<vec> mat;

long long n, k;

mat mul(mat &a, mat &b) {
	// a: m*s, b: s*n, c: m*n
	static mat c(n, vec(n, 0));
	// clear
	for (int i(0); i < n; ++i) c[i].assign(n, 0);
	
	for (int k(0); k < n; ++k)
		for (int i(0); i < n; ++i)
			for (int j(0); j < n; ++j)
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
	return c;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	
	mat mt(n, vec(n, 0));
	for (int i(0); i < n; ++i) {
		for (int j(0); j < n; ++j)
			cin >> mt[i][j];
	}
	
	mat res(n, vec(n, 0));
	for (int i(0); i < n; ++i) res[i][i] = 1;
	
	while (k) {
		if (k & 1) res = mul(res, mt);
		mt = mul(mt, mt), k >>= 1;
	}
	
	// printMat(res);
	for (int i(0); i < n; ++i) {
		for (int j(0); j < n; ++j)
			cout << res[i][j] % MOD << ' ';
		cout << endl;
	}
	
	return 0;
}