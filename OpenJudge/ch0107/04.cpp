/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0107/04
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

int main() {
	int n;
	cin >> n;

	stringstream ss;

	for (int i = 0; i < n; i++) {
		string a, b;
		cin >> a >> b;
		if (a[0] == b[0]) {
			cout << "Tie" << endl;
			continue;
		}
		if (a[0] == 'R') {
			if (b[0] == 'P') {
				cout << "Player2" << endl;
			} else {
				cout << "Player1" << endl;
			}
		} else if (a[0] == 'P') {
			if (b[0] == 'S') {
				cout << "Player2" << endl;
			} else {
				cout << "Player1" << endl;
			}
		} else {
			if (b[0] == 'R') {
				cout << "Player2" << endl;
			} else {
				cout << "Player1" << endl;
			}
		}
	}
}
