/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0109/13/
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

void append(vector<int> & v, int x) {
	for (const int &n : v) {
		if (n == x) return;
	}
	v.push_back(x);
}

int main() {
	int n;
	cin >> n;

	vector<int> v;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		append(v, t);
	}

	for (const int &n : v)
		cout << n << ' ';

	return 0;
}
