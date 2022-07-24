/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0107/08
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
	char o, a;
	cin >> s >> o >> a;

	for (char &c : s) {
		if (c == o) c = a;
	}

	cout << s << endl;
}
