/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0109/12/
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
	int n;
	cin >> n;

	int mx = 0;

	int len = 0;
	int prev, cur;
	cin >> prev;
	for (int i = 1; i < n; i++) {
		cin >> cur;
		if (prev == cur) len++;
		else mx = max(mx, len+1), len = 0;
		prev = cur;
	}

	mx = max(mx, len+1);

	cout << mx << endl;
}
