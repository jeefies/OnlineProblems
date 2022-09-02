/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1015
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

bool isPalindrome(string & n) {
	int l = 0, r = n.size() - 1;
	bool ok = true;
	while (l < r) {
		if (n[l++] != n[r--])
			ok = false;
	}
	return ok;
}

int toPalindrome(int base, string & num) {
	static int step = 0;

	if (step >= 30) {
		return -1;
	}

	if (isPalindrome(num)) return step;

	++step;
	string next;
	char rest = 0;
	for (int i = 0, r = num.size() - 1; r >= 0; i++, r--) {
		int tmp;
		next += (tmp = rest + num[i] + num[r]) % base;
		rest = tmp / base;
	}

	if (rest) next += rest;

	return toPalindrome(base, next);
}

int main() {
	int base;
	cin >> base;

	string num;
	cin >> num;

	for (char & c : num) {
		if ('0' <= c && c <= '9') c -= '0';
		else if ('a' <= c && c <= 'z') c = c - 'a' + 10;
		else if ('A' <= c && c <= 'Z') c = c - 'A' + 10;
	}

	int steps = toPalindrome(base, num);
	if (steps == -1) cout << "Impossible!" << endl;
	else cout << "STEP=" << steps << endl;
}
