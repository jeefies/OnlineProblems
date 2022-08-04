/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0203/1788/
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

int pell(int n) {
	int a = 1, b = 2;
	if (n == 1) return 1;
	if (n == 2) return 2;

	int c;
	n -= 2;
	while (n-- > 0) {
		c = 2 * b + a;
		a = b;
		b = c % 32767;
	}

	return b;
}

int main() {
	int cnt;
	cin >> cnt;
	while (cnt-- > 0) {
		int n; cin >> n;
		cout << pell(n) << endl;
	}
}
