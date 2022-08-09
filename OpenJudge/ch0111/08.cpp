/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0111/08/
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
bool nums[100010] = {false};

#warning "这个程序只能得9分，还有1分不知道错在哪里"

int main() {
	int n;
	cin >> n;
	while (n--) {
		int x;
		cin >> x;
		nums[x] = true;
	}

	for (int i = 1; i < 100000; i++) {
		if (nums[i]) cout << i << ' ';
	}
}
