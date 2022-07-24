/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0107/07
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
	string g;
	getline(cin, g);

	for (const char &c : g) {
		if (c == 'T') putchar('A');
		else if (c == 'A') putchar('T');
		else if (c == 'G') putchar('C');
		else putchar('G');
	}
}
