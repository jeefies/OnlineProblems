/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0111/01/
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

int findclosest(vector<int> & v, int x) {
	int l = 0, r = v.size() - 1;
	int mid = r / 2;

	while (true) {
		if (l >= r) return v[l];

		if (l + 1 == r) {
			if (x - v[l] <= v[r] - x) return v[l];
			else return v[r];
		}

		if (v[mid] == x) return x;
		
		if (v[mid] > x) {
			r = mid;
			mid = (l + r) / 2;
		} else {
			l = mid;
			mid = (l + r) / 2;
		}
	}
}

int main() {
	int n;
	cin >> n;
	
	vector<int> v;

	while (n-- > 0) {
		int x;
		cin >> x;
		v.push_back(x);
	}

	cin >> n;
	while (n-- > 0) {
		int x;
		cin >> x;
		cout << findclosest(v, x) << endl;
	}
	return 0;
}
