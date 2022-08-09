/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0110/02/
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

void append(vector<int> & v, int n) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] >= n) {
			auto it = v.begin();
			v.insert(it + i, n);
			return;
		}
	}

	v.push_back(n);
}


int main() {
	int n;
	cin >> n;

	vector<int> v;

	while (n-- > 0) {
		int x;
		cin >> x;
		if (x % 2 == 1)
			append(v, x);
	}

	cout << v[0];
	for (int i = 1; i < v.size(); i++)
		cout << ',' << v[i];
	cout << endl;
	return 0;
}
