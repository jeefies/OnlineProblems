/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL : http://noi.openjudge.cn/ch0106/10/
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
	string as, bs, temps;
	getline(cin, as);
	getline(cin, bs);

	if (as.length() < bs.length()) {
		temps = as;
		as = bs;
		bs = temps;
		// cout << "as:" << as << endl;
		// cout << "bs:" << bs << endl;
	}

	int minl, restl;
	minl = bs.length();
	restl = as.length() - minl;

	string rs;
	int x = 0, s = 0;
	reverse(as.begin(), as.end());
	reverse(bs.begin(), bs.end());

	for (int i = 0; i < minl; i++) {
		x = as[i] + bs[i] - '0' - '0' + s;
		s = x / 10;
		x = x % 10;
		rs += x + '0';
	}

	for (int i = 0; i < restl; i++) {
		x = as[i + minl] - '0' + s;
		s = x / 10;
		x = x % 10;
		rs += x + '0';
	}

	rs += s + '0';

	// cout << "rs:" << rs << endl;
	int i = 0;
	reverse(rs.begin(), rs.end());
	while (rs.length() > 1 && rs[i] == '0')
		i++;
	int is0 = 1;
	for (; i < rs.length(); i++) {
		is0 = 0;
		putchar(rs.at(i));
	}
	if (is0) putchar('0');
}
