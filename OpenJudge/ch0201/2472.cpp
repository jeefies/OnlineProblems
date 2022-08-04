/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL : http://noi.openjudge.cn/ch0201/2472/
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

void insert(vector< pair<string, int> > &subs, string s, int pos, int len) {
	string sub(s, pos, len);
	// cout << sub << endl;
	for (int i = 0; i < subs.size(); i++) {
		// cout << '\t' << subs[i].first << ' ' << subs[i].second << endl;
		if (sub == subs[i].first) {
			subs[i].second++;
			return;
		}
		if (sub < subs[i].first) {
			auto it = subs.begin();
			subs.insert(it + i, make_pair(sub, 1));
			return;
		}
	}

	subs.push_back(make_pair(sub, 1));
}

int main() {
	vector< pair<string, int> > subs;
	string ms;
	cin >> ms;

	for (int len = 1; len <= ms.length(); len++) {
		for (int i = 0; i <= ms.length() - len; i++) {
			insert(subs, ms, i, len);
		}
	}

	for (int i = 0; i < subs.size(); i++) {
		if (subs[i].second > 1)
			printf("%s %d\n", subs[i].first.c_str(), subs[i].second);
	}

	return 0;
}
