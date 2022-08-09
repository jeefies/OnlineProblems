/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0109/11/
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
	int k;
	cin >> k;

	// Ignore '\n'
	getchar();
	
	string s;
	getline(cin, s);

	int n = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == s[i+1]) {
			// 需要加上下一个才是连续出现的次数
			if (++n + 1 >= k) {
				cout << s[i] << endl;
				return 0;
			}
		} else n = 0;
	}

	cout << "No" << endl;
	return 0;
}
