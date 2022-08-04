/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0203/6262/
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

char rooms[102][102] = {0};

int n;


void print() {
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			cout << rooms[x][y];
		}
		cout << endl;
	}
}

void spreadFlu(int x, int y) {
	// print();
	x--;
	if (rooms[x][y] == '.') rooms[x][y] = '@';
	x++;
	y++;
	if (rooms[x][y] == '.') rooms[x][y] = '@';
	x++;
	y--;
	if (rooms[x][y] == '.') rooms[x][y] = '@';
	x--;
	y--;
	if (rooms[x][y] == '.') rooms[x][y] = '@';
	// print();
	// printf("\n");
}

void check() {
	char copy[102][102];
	memcpy(copy, rooms, 102 * 102);

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			if (copy[x][y] == '@') {
				spreadFlu(x, y);
			}
		}
	}
}

int count()  {
	int  c = 0;
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			if (rooms[x][y] == '@') c++;
		}
	}
	return c;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> rooms[i][j];
		}
	}
	int days;
	cin >> days;
	while (days-- - 1 > 0) check();
	cout << count() << endl;
}
