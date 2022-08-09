/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0110/01/
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

using namespace std;

typedef pair<string, int> pinfo;

void append(vector<pinfo> & v, string name, int score) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].second < score) {
			auto it = v.begin();
			v.insert(it + i, make_pair(name, score));
			return;
		}

		if (v[i].second == score) {
			if (v[i].first > name) {
				auto it = v.begin();
				v.insert(it + i, make_pair(name, score));
				return;
			}
		}
	}

	v.push_back(make_pair(name, score));
}

int main() {
	int n;
	cin >> n;

	vector<pinfo> v;

	while (n-- > 0) {
		string name;
		int score;
		cin >> name >> score;
		append(v, name, score);
	}

	for (const pinfo & pi : v) {
		cout << pi.first << ' ' << pi.second << endl;
	}
}
