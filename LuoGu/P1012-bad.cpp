/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1012
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

#warning This is a very slow version for the first time i write.

string read() {
	string r;
	char tmp;
	while (isspace(tmp = getchar()));
	while ('0' <= tmp && tmp <= '9') {
		r += tmp;
		tmp = getchar();
	}
	return r;
}

bool cmp(string & a, string & b) {
	return a[0] > b[0];
}

string mymax(string & a, string b) {
	if (a.size() > b.size()) return a;
	if (a.size() < b.size()) return b;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] > b[i]) return a;
		if (a[i] < b[i]) return b;
	}
	// equal
	return a;
}

string search(string * nums, int l, int r, int i, int k) {
	if (k == 1) return nums[i];
	static bool used[20] = {false};

	used[i] = true;

	string maxs;
	for (int d = l; d < r; d++) {
		if (!used[d])
			maxs = mymax(maxs, nums[i] + search(nums, l, r, d, k - 1));
	}

	used[i] = false;

	return maxs;
}

string sameprefixsearch(string * nums, int l, int r) {
	if (l + 1 == r) return nums[l];
	string maxs;

	for (int i = l; i < r; i++) {
		maxs = mymax(maxs, search(nums, l, r, i, r - l));
	}

	return maxs;
}

int main() {
	int n;
	cin >> n;
	string nums[20];

	for (int i = 0; i < n; i++)
		nums[i] = read();

	sort(nums, nums + n, cmp);

	char fc = nums[0][0];
	int l = 0, r = 0;
	string ret;
	for (int i = 0; i < n; i++) {
		if (nums[i][0] != fc) {
			fc = nums[i][0];
			ret += sameprefixsearch(nums, l, i);
			l = i;
		}
	}
	ret += sameprefixsearch(nums, l, n);

	cout << ret << endl;
}
