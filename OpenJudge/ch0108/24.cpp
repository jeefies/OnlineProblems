/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0108/24/
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>

using namespace std;

int map[11][11] = {0};

void printer() {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			if (map[i][j] != 0)
				cout << map[i][j] << ' ';
		}
		cout << endl;
	}
}

void setter(int x, int y) {
	static int cnt = 0;
	// printf("set at (%d, %d)\n", x, y);
	map[x][y] = ++cnt;
}

int main() {
	int a;
	cin >> a;

	int x = 0, y = 0;
	for (int i = 0; i < a; i++) {
		if (i % 2 == 0) {
			x = i; y = 0;
			for (; x >= 0; y++, x--) {
				setter(x, y);
			}
		} else {
			x = 0; y = i;
			for (; y >= 0; y--, x++) {
				setter(x, y);
			}
		}
	}

	for (int i = a - 1; i > 0; i--) {
		if (i % 2 == 1) {
			x = a - 1; y = a - i;
			for (; y < a; y++, x--) {
				setter(x, y);
			}
		} else {
			x = a - i; y = a - 1;
			for (; x < a; y--, x++) {
				setter(x, y);
			}
		}
	}

	printer();
}
