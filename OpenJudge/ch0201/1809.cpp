/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		origin url: http://noi.openjudge.cn/ch0201/1809/
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

int nums[100] = {0};

int main() {
	int n;

	// freopen("test.in", "r", stdin);

	while (cin >> n) {
		nums[n] = 1;
	}

	int cnt = 0;
	// ignore 0
	for (int i = 1; i < 50; i++) {
		if (nums[i] != 0 && nums[i * 2] != 0) {
			cnt++;
			// cout << i << endl;
		}
	}

	cout << cnt << endl;
}
