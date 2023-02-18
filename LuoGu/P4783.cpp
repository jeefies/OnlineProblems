#include <iostream>
#include <algorithm>

using namespace std;
const int N = 400, MOD = 1e9 + 7;

int n, mat[N][N<<1];

int qpow(int a, int x, int p) {
	int r(1);
	while (x) {
		if (x & 1) r = (long long)r * a % p;
		a = (long long)a * a % p, x >>= 1;
	}
	return r;
}

#define inv(x) (qpow(x, MOD - 2, MOD))
#define update(x, y) (x) = (long long)(x) * y % MOD;

inline int mod(long long x) {
	x %= MOD;
	return x < 0 ? x + MOD : x;
}

void prt() {
	for (int i(0); i < n; ++i) {
		for (int j(0); j < (n << 1); ++j)
			cout << mat[i][j] << ' ';
		cout << '\n';
	}
	cout << '\n';
}

bool Gauss() {
	const int ne = n << 1;

	for (int i(0); i < n; ++i) { // proc row i
		int mx(mat[i][i]), mj(i);
		for (int j(i + 1); j < n; ++j) {
			if (mat[j][i] > mx) mx = mat[j][i], mj = j;
		}

		if (mx == 0) return false;

		// change line
		swap(mat[i], mat[mj]);

		// remove line
		int invx = inv(mx);
		for (int j(i); j < ne; ++j)
			update(mat[i][j], invx);

		// remove row
		for (int j(0); j < n; ++j) {
			if (j == i) continue;
			for (int k = ne - 1; k >= i; --k)
				mat[j][k] = mod(mat[j][k] - (long long)mat[i][k] * mat[j][i]);
		}
	}
	return true;
}

int main() {
	cin.tie(0)->sync_with_stdio(false);

	cin >> n;
	for (int i(0); i < n; ++i) {
		mat[i][i + n] = 1;
		for (int j(0); j < n; ++j) 
			cin >> mat[i][j];
	}

	if (!Gauss()) {
		puts("No Solution");
		return 0;
	}

	for (int i(0); i < n; ++i) {
		for (int j(0); j < n; ++j)
			cout << mat[i][j + n] << ' ';
		cout << '\n';
	}

	return 0;
}
