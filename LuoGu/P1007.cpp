/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1007
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
#include <climits>

using namespace std;

int main() {
	int L, n;
	cin >> L >> n;
	if (n == 0) { cout << "0 0" << endl; return 0; }
	int mint = INT_MIN, maxt = INT_MIN, tmp, lt;
	for (int i = 0; i < n; i++) {
		cin >> tmp;
		lt = L + 1 - tmp;
		maxt = max(maxt, max(tmp, L + 1 - tmp));
		mint = max(mint, min(tmp, L + 1 - tmp));
	}
	cout << mint << ' ' << maxt << endl;
	return 0;
}
