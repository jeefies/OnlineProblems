/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0203/3525/
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

int step(int n) {
	int a = 1, b = 2, c = 4;
	if (n == 1) return 1;
	if (n == 2) return 2;
	if (n == 3) return 4;

	n -= 3;
	int d;
	while (n-- > 0) {
		d = a + b + c;
		a = b;
		b = c;
		c = d;
	}

	return d;
}

int main() {
	while(1) {
		int n; cin >> n;
		if (n == 0) break;
		cout << step(n) << endl;
	}
}
