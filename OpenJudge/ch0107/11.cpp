/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0107/11
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

char codes[26] = {0};

int main() {
	string pwd, origin, want;

	getline(cin, pwd);
	getline(cin, origin);
	getline(cin, want);

	for (int i = 0; i < origin.size(); i++) {
		int ci = pwd[i] - 'A';
		if (codes[ci] != 0 && origin[i] != codes[ci]) {
			printf("Failed\n");
			return 0;
		}

		codes[ci] = origin[i];
	}

	char dst[26] = {0};
	for (int i = 0; i < 26; i++) {
		if (codes[i] == 0 || !('A' <= codes[i] && codes[i] <= 'Z')) {
			printf("Failed\n");
			return 0;
		}
		dst[codes[i] - 'A']++;
		if (dst[codes[i] - 'A'] > 1) {
			printf("Failed\n");
			return 0;
		}
	}

	for (const char &c : want) {
		putchar(codes[c - 'A']);
	}
	putchar('\n');
}
