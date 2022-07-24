/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0107/06
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

bool isDigit(char c) {
	if ('0' <= c && c <= '9') return true;
	return false;
}

bool isValid(char c) {
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_') return true;
	return false;
}

int main() {
	string s;
	getline(cin, s);

	if (!isValid(s[0])) {
		cout << "no\n";
		return 0;
	}

	for (int i = 1; i < s.size(); i++) {
		if (!isValid(s[i]) && !isDigit(s[i])) {
			cout << "no\n";
			return 0;
		}
	}

	cout << "yes\n";
	return 0;
}
