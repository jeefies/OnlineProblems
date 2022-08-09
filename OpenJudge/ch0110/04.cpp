/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0110/04/
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
#include <utility>
#include <tuple>

using namespace std;

// total, chinese, id
typedef tuple<int, int, int> stu;

void append(vector<stu> & v, int total, int chinese, int id) {
	auto it = v.begin();
	auto nstu = make_tuple(total, chinese, id);
	// cout << "Append In" << endl;

	for (int i = 0; i < v.size(); i++) {
		auto vi = v[i];
		if (get<0>(vi) < total) {
			v.insert(it + i, nstu);
			return;
		}

		if (get<0>(vi) == total) {
			if (get<1>(vi) < chinese) {
				v.insert(it + i, nstu);
				return;
			} else if (get<1>(vi) == chinese) {
				if (get<2>(vi) >= id) {
					v.insert(it + i, nstu);
					return;
				}
			}
		}
	}

	v.push_back(nstu);
}

int main() {
	int n;
	cin >> n;
	vector<stu> v;
	for (int id = 0; id < n; id++) {
		int a, b, c;
		cin >> a >> b >> c;
		append(v, a + b + c, a, id + 1);
	}

	// cout << "v size " << v.size() << endl;
	for (int i = 0; i < 5; i++) {
		cout << get<2>(v[i]) << ' ' << get<0>(v[i]) << endl;
	}
}
