/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0107/05
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
	string s;
	getline(cin, s);

	char tmp = s[0];
	int i = 0;
	for (; i < s.size() - 1; i++) {
		s[i] += s[i + 1];
	}

	s[i] += tmp;

	cout << s << endl;
}
