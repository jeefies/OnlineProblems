/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>

const int CAN = 1;
const int NO = 0;

using namespace std;

int bx, by, mx, my;
long long map[25][25];

int set(int x, int y, int val);
long long get(int x, int y);

int main(){
	cin >> bx >> by >> mx >> my;

	for (int i = 0; i <= bx; i++) {
		for (int j = 0; j <= by; j++) {
			map[i][j] = CAN;
		}
	}

	// Set no steps
	set(mx, my, 0);
	set(mx + 2, my + 1, NO);
	set(mx + 2, my - 1, NO);
	set(mx + 1, my + 2, NO);
	set(mx + 1, my - 2, NO);
	set(mx - 1, my + 2, NO);
	set(mx - 1, my - 2, NO);
	set(mx - 2, my + 1, NO);
	set(mx - 2, my - 1, NO);

	for (int j = 0; j <= by; j++) {
		for (int i = 0; i <= bx; i++) {
			map[0][0] = 1;
			if (get(i, j) == NO) continue;
			map[i][j] = get(i - 1, j) + get(i, j - 1);
		}
	}

	cout << map[bx][by];

    return 0;
} 

int set(int x, int y, int val) {
	if (x < 0 || x >= 25 || y < 0 || y >= 25) return 1;
	map[x][y] = val;
	return 0;
}

long long get(int x, int y) {
	if (x < 0 || x >= 25 || y < 0 || y >= 25) return 0;
	return map[x][y];
}
