/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0201/2722/
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

bool checks[20001] = {false};

int main() {
	int n;
	cin >> n;
	vector<int> nums;
	while (n-- > 0) {
		int i = 0;
		cin >> i;
		checks[i] = true;
		nums.push_back(i);
	}

	int total = 0;
	for (int l = 0; l < nums.size(); l++) {
		for (int r = l + 1; r < nums.size(); r++) {
			if (checks[nums[l] + nums[r]]) {
				checks[nums[l] + nums[r]] = false;
				total++;
			}
		}
	}

	cout << total << endl;
}
