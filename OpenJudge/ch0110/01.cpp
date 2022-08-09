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

typedef pair<int, double> pinfo;

void append(vector<pinfo> & v, int id, double n) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].second <= n) {
			auto it = v.begin();
			v.insert(it + i, make_pair(id, n));
			return;
		}
	}

	v.push_back(make_pair(id, n));
}

int main() {
	int n, k;
	cin >> n >> k;

	vector<pinfo> v;

	while (n-- > 0) {
		int id;
		double score;
		cin >> id >> score;
		append(v, id, score);
	}

	printf("%d %g\n", v[k-1].first, v[k-1].second);
}
