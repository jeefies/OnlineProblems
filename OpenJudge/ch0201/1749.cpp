/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0201/1749/
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

int nums[3];

int main() {
	int n;
	cin >> n;
	nums[0] = nums[1] = nums[2] = n;
	// 0 <= 1 <= 2
	
	int max = 0;

	for (int a = 0; a <= n; a++) {
		for (int b = 0; b <= n; b++) {
			if ((a + b) % 2 != 0) continue;

			for (int c = 0; c <= n; c++) {
				if ((b + c) % 3 != 0) continue;
				int sum = a + b + c;
				if (sum % 5 != 0) continue;

				if (sum > max) max = sum;
			}
		}
	}

	cout << max << endl;
}
