/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0202/2705/
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
#include <stack>

using namespace std;

string checkLine(string line) {
	stack<int> leftp;
	stack<int> rightp;
	char * r = (char *)malloc(sizeof(char) * (line.size() + 1));
	r[line.size()] = '\0';

	for (int i = 0; i < line.size(); i++) {
		r[i] = ' ';
		if (line[i] == '(') {
			leftp.push(i);
		} else if (line[i] == ')') {
			if (leftp.size() == 0) {
				r[i] = '?';
			} else {
				leftp.pop();
			}
		}
	}

	while (!leftp.empty()) {
		r[leftp.top()] = '$';
		leftp.pop();
	}

	return r;
}

int main() {
	string line;
	while (getline(cin, line)) {
		cout << line << endl;
		cout << checkLine(line) << endl;
	}
}
