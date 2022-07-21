/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>

using namespace std;

int main() {
	string s;
	getline(cin, s);
	int prev_is_space = 0;

	for (const char &tmp : s) {
		if (tmp == ' ' && prev_is_space) {
			continue;
		}
		if (tmp == ' ')
			prev_is_space = 1;
		else
			prev_is_space = 0;
		putchar(tmp);
	}
}
