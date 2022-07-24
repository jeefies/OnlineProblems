/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0106/11
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

int main() {
	string a, b;

	getline(cin, a);
	getline(cin, b);

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	string rs;

	int x = 0, s = 0;
	for (int i = 0; i < b.size(); i++) {
		x = a[i] - b[i] - s;
		s = 0;
		while (x < 0) {
			x += 10;
			s += 1;
		}
		rs += x + '0';
	}

	for (int i = b.size(); i < a.size(); i++) {
		x = a[i] - '0' - s;
		s = 0;
		while (x < 0) {
			x += 10;
			s += 1;
		}
		rs += x + '0';
	}

	int is0 = 1;
	int m = rs.size() - 1;
	while (m > 0 && rs[m] == '0') {
		m--;
	}

	for (; m >= 0; m--) {
		putchar(rs.at(m));
	}

	return 0;
}
