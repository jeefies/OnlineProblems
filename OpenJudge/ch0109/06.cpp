/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0108/24/
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>

using namespace std;

int valid(int x, int y) {
	// printf("maxn %d, minn %d\n", x, y);
	int s = x - y;
	if (s <= 1) return 0;
	for (int i = 2; i * i < s; i++) {
		if (s % i == 0)
			return 0;
	}
	return 1;
}

int main() {
	string word;
	getline(cin, word);

	char bitmap[26] = {0};
	for (const char &c : word) {
		bitmap[c-'a']++;
	}

	int maxn = 0, minn = 1000;
	for (int i = 0; i < 26; i++) {
		if (bitmap[i] == 0) continue;
		maxn = bitmap[i] > maxn ? bitmap[i] : maxn;
		minn = bitmap[i] > minn ? minn : bitmap[i];
	}

	if (valid(maxn, minn)) {
		printf("Lucky Word\n%d\n", maxn - minn);
	} else {
		printf("No Answer\n0\n");
	}
}
