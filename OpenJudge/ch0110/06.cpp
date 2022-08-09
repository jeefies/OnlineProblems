/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0110/06/
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

int nums[101] = {0};

int main() {
	for (int i = 0; i < 10; i++) {
		int x;
		cin >> x;
		nums[x]++;
	}

	for (int i = 99; i > 0; i -= 2) {
		while (nums[i]-- > 0)
			cout << i << ' ';
	}

	for (int i = 0; i <= 100; i += 2) {
		while (nums[i]-- > 0)
			cout << i << ' ';
	}
	return 0;
}
