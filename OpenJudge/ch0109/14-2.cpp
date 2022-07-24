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
	cin >> n;
	getchar();

	vector<string> carpets;

	string s;
	for (int i = 0; i < n; i++) {
		getline(cin, s);
		carpets.push_back(s);
	}
	cin >> x >> y;

	for (int i = n - 1; i >= 0; i--) {
		int a, b, g, k;
		// cout << "Carpets" << i << " : " << carpets[i] << endl;
		sscanf(carpets[i].c_str(), "%d%d%d%d", &a, &b, &g, &k);
		// printf("%d %d %d %d\n", a, b, g, k);
		if (a <= x && x <= a + g && b <= y && y <= b + k) {
			cout << i + 1 << endl;
			return 0;
		}
	}
	cout << -1 << endl;
}
