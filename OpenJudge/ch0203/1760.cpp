/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0203/1760/
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

int fib(int n) {
	int a = 1;
	int b = 1;
	if (n <= 2) return 1;
	n -= 2;
	while (n-- > 0) {
		b = a + b;
		a = b - a;
		b %= 1000;
	}

	return b;
}

int main() {
	int cnt;
	cin >> cnt;
	while (cnt-- > 0) {
		int n;
		cin >> n;
		cout << fib(n) << endl;
	}
}
