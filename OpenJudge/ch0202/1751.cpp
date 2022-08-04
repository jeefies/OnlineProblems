/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0202/1751/
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

int getNum(int x, int min) {
	// 从小到大
	if (x < min) return 0;

	int c = 0;
	for (int i = min; i < x; i++) {
		if (x % i == 0) {
			c += getNum(x / i, i);
		}
	}

	// 当i==x时，必定有一种情况
	c++;
	return c;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		cout << getNum(x, 2) << endl;
	}
}
