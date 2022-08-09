/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0111/07/
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

#warning "这个程序只能得9分，还有1分不知道错在那里"

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> v;
	
	while (n--) {
		int x;
		cin >> x;
		v.push_back(x);
	}

	int target;
	cin >> target;

	sort(v.begin(), v.end());

	int l = 0, r = v.size() - 1;

	while (l <= r) {
		while (l <= r && v[l] + v[r] > target) {
			r--;
		}

		while (l <= r && v[l] + v[r] < target) {
			l++;
		}

		if (l <= r && v[l] + v[r] == target) {
			cout << v[l] << ' ' << v[r] << endl;
			return 0;
		}
	}

	cout << "No" << endl;
	return 0;
}
