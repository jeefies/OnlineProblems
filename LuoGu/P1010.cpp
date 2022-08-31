/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1010
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

string show(int i, bool outer = false) {
	// 递归的边界条件，0是为了处理2(0)
	if (i == 0) return "0";
	else if (i == 1) return "2(0)";
	else if (i == 2) return "2";

	string r;

	int bit = 1;
	while (i) {
		if (i & 1) {
			if (bit != 2) r = "2(" + show(bit - 1, bit > 2) + ")" + r;
			else r = "2" + r;

			// 如果之后还需要用其他的数加，则需要这个加号
			if (i >> 1) r = "+" + r;
		}
		i >>= 1, bit++;
	}
	
	return r;
}

int main() {
	int n;
	cin >> n;
	cout << show(n) << endl;
}
