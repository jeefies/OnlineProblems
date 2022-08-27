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
#include <tuple>

int n;
int x, y;

using namespace std;

typedef tuple<int, int, int, int> carpet;

carpet carpets[10001];

int main() {
	cin >> n;

	int a, b, g, k;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> g >> k;
		carpets[i] = make_tuple(a, b, g, k);
	}

	cin >> x >> y;

	for (int i = n - 1; i >= 0; i--) {
		tie(a, b, g, k) = carpets[i];
		if (a <= x && x <= a + g && b <= y && y <= b + k) {
			cout << i + 1 << endl;
			return 0;
		}
	}
	cout << -1 << endl;
	return 0;
}
