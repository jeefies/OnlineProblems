/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		http://noi.openjudge.cn/ch0201/1752/
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
	int feet;
	cin >> feet;

	if (feet % 2 != 0 || !feet) {
		cout << "0 0\n";
		return 0;
	}

	int minn = feet / 4 + (feet % 4) / 2;
	int maxn = feet / 2;

	cout << minn << ' ' << maxn << endl;
}
