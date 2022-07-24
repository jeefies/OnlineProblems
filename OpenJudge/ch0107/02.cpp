/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0107/02/
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
	string line;
	getline(cin, line);

	int chars[26] = {0};
	
	for (const char &c : line) {
		chars[c-'a']++;
	}

	for (const char &c : line) {
		if (chars[c-'a'] == 1) {
			cout << c << endl;
			return 0;
		}
	}

	cout  << "no\n";
}
