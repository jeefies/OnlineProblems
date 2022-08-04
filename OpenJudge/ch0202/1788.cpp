/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0202/1788/
 */

#include <iostream>
using namespace std;

int MAX = 32767;

int pell(int n) {
	if (n <= 1) return 1;
	if (n == 2) return 2;
	int a = 1, b = 2, c;
	for (int i = 2; i < n; i++) {
		c = (b * 2  + a) % MAX;
		a = b;
		b = c;
	}
	return c;
}

int main() {
	int n;
	cin >> n;

	while (n-- > 0) {
		int c;
		cin >> c;
		cout << pell(c) << endl;
	}
	
}
