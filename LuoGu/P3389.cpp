#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef vector<double> vec;
typedef vector<vec> mat;

void init(mat &ma, int n, int m) {
	ma.resize(n);
	for (auto &v : ma) v.assign(m, 0);
}

template<typename T>
inline T abs(const T & v) {
	return v < 0 ? -v : v;
}

const double eps(1e-7);
bool Gauss(mat &m) {
	int n = m.size();
	
	for (register int col(0); col ^ n; ++col) {
		// cout << "At col " << col << endl;
		// find greatest line
		register int x(col), r(col), j, c;
		for (; r < n; ++r) {
			if (abs(m[r][col]) > abs(m[x][col])) x = r;
		}
		
		// make this line to col
		swap(m[x], m[col]), x = col;
		
		if (abs(m[x][col]) < eps) return false;
		
		register double div = m[x][col];
		for (int j(0); j <= n; ++j) m[x][j] /= div;
		
		// cout << "Line changed" << endl;
		// printMat(m);
		// cout << "Clear col " << col << endl;
		// clear line elements
		for (j = 0; j ^ n; ++j) {
			if (j ^ col) {
				div = m[j][col] / m[x][col];
				for (c = col + 1; c <= n; ++c) {
					m[j][c] -= m[x][c] * div;
				}
			}
		}

		// printMat(m);
	}
	
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << fixed << setprecision(2);
	
	int n;
	cin >> n;
	register int i, j;
	
	mat m; init(m, n, n + 1);
	for (i = 0; i ^ n; ++i) {
		for (j = 0; j <= n; ++j)
			cin >> m[i][j];
	}
	
	if (!Gauss(m)) {
		cout << "No Solution" << endl;
		return 0;
	}
	
	for (i = 0; i ^ n; ++i) {
		cout << m[i][n] / m[i][i] << endl;
	}
	
	return 0;
}