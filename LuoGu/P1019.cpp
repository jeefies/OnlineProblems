/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1019
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

int n;
string words[20];
int used[20];

int getPrefix(int p, int n) {
	string pre = words[p], nxt = words[n];
	for (int pi = pre.size() - 1; pi >= 0; pi--) {
		// prevent case like pre is 'what' and nxt is 'ha'
		if (pi + nxt.size() < pre.size()) break;

		bool right = true;
		int i = pi;
		for (int ni = 0; i < pre.size(); ni++) {
			if (pre[i++] != nxt[ni]) {
				right = false;
				break;
			}
		}

		if (right) return pre.size() - pi;
	}
	// no same prefix or total include.
	return -1;
}

long unsigned int search(int c, int depth) {
	used[c]--;

	long unsigned int maxl = words[c].size();

	for (int i = 0; i < n; i++) {
		if (used[i] == 0) continue;

		int prefixL = getPrefix(c, i);
		if (prefixL == -1) continue;
		maxl = max(maxl, search(i, depth + 1) + words[c].size() - prefixL);
	}
	
	used[c]++;
	return maxl;
}

int main() {
	cin >> n;
	while (getchar() != '\n'); // ignore '\n'
	for (int i = 0; i < n; i++) {
		cin >> words[i];
		used[i] = 2;
	}

	char start;
	cin >> start;

	long unsigned int maxl = 0;
	for (int i = 0; i < n; i++) {
		if (words[i][0] == start) {
			maxl = max(maxl, search(i, 0));
		}
	}

	cout << maxl << endl;
}
