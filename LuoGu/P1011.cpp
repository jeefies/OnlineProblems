/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL : https://www.luogu.com.cn/problem/P1011
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

class Number {
public:
	int a, x;
	Number(int _a = 0, int _x = 0) { a = _a, x = _x; }

	Number operator+(const Number & n) {
		Number r(a + n.a, x + n.x);
		return r;
	}

	Number operator-(const Number & n) {
		Number r(a - n.a, x - n.x);
		return r;
	}
};

int main() {
	int a, n, m, x;
	cin >> a >> n >> m >> x;

	if (x == n) {
		cout << 0 << endl;
		return 0;
	} else if (x == 1 || x == 2) {
		cout << a << endl;
		return 0;
	} else if (x == 3) {
		cout << a * 2 << endl;
		return 0;
	}

	Number d, t(1, 0), cu(0, 1), cd(0, 1), pu(1, 0);

	for (int i = 3; i < n; i++) {
		// 简化代码的小技巧，重载与等号
		pu = (cu = (cd = cu) + pu) - pu;
		t = t + cu - cd;
		if (i == x) d = t;
	}

	int ux = (m - t.a * a) / t.x;
	cout << d.a * a + d.x * ux << endl;
	return 0;
}
