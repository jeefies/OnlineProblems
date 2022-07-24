/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0109/14/
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>

int n;
int x, y;

using namespace std;

int main() {
	stringstream ss;
	cin >> n;
	getchar();
	string s;
	for (int i = 0; i < n; i++) {
		getline(cin, s);
		ss << s << endl;
	}
	cin >> x >> y;

	int id = -1;
	for (int i = 0; i < n; i++) {
		int a, b, g, k;
		ss >> a >> b >> g >> k;
		// printf("%d %d %d %d\n", a, b, g, k);
		if (a <= x && x <= a + g && b <= y && y <= b + k) {
			id = i + 1;
		}
	}
	cout << id << endl;
}
