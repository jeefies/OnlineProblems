/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0201/2723/
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
	int n, m;
	cin >> n >> m;
	for (int l = 1, r = m - 1; l <= r; l++, r--) {
		if (n % l == 0 && n % r == 0) {
			cout << l << endl;
			return 0;
		}
	}
	cout << "-1\n";
	return 0;
}
