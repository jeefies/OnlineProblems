/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0201/1973/
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
	string p, q, r;
	cin >> p >> q >> r;
	char maxn = 0;

	for (char &c : p) {
		c -= '0';
		maxn = max(c, maxn);
	}
	for (char &c : q) {
		c -= '0';
		maxn = max(c, maxn);
	}
	for (char &c : r) {
		c -= '0';
		maxn = max(c, maxn);
	}

	int ip, iq, ir;
	for (int i = maxn + 1; i <= 16;i++) {
		ip = iq = ir = 0;
		for (const char &c : p)
			ip = ip * i + c;
		for (const char &c : q)
			iq = iq * i + c;
		for (const char &c : r)
			ir = ir * i + c;

		if (ip * iq == ir) {
			cout << i << endl;
			return 0;
		}
	}

	cout << 0 << endl;
	return 0;
}
