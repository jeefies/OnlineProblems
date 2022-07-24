/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0107/10
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

char codes[27] = "VWXYZABCDEFGHIJKLMNOPQRSTU";

int main() {
	string pwd;
	getline(cin, pwd);

	for (char &c : pwd) {
		if ('A' <= c && c <= 'Z') c = codes[c - 'A'];
	}

	cout << pwd << endl;
}
