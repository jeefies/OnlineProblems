/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		https://www.luogu.com.cn/problem/P2196
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

typedef vector<int> vi;

void search(int i, vector<vi> & caves, vi & bombs, vi & cleans, vi & children) {
	if (cleans[i] != -1) return;

	if (caves[i].size() == 0) {
		cleans[i] = bombs[i];
		children[i] = -1;
		return;
	}

	for (const int child : caves[i]) {
		search(child, caves, bombs, cleans, children);
		if (cleans[child] + bombs[i] > cleans[i]) {
			cleans[i] = cleans[child] + bombs[i];
			children[i] = child;
		}
	}
}

int main() {
	int n;
	cin >> n;
	vector<vi> caves(n);
	vector<int> bombs(n);
	vector<int> cleans(n);
	vector<int> children(n);

	for (int i = 0; i < n; i++) {
		cin >> bombs[i];
		cleans[i] = -1;
	}

	char t;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			cin >> t;
			if (t == '1')
				caves[i].push_back(j);
		}
	}

	for (int i = 0; i < n; i++) {
		search(i, caves, bombs, cleans, children);
	}

	int maxn = INT_MIN, maxs;

	for (int i = 0; i < n; i++) {
		if (cleans[i] > maxn) maxs = i, maxn = cleans[i];
	}

	cout << maxs + 1 << ' ';
	while (children[maxs] != -1) {
		cout << children[maxs] + 1 << ' ';
		maxs = children[maxs];
	}

	cout << endl << maxn << endl;
}
