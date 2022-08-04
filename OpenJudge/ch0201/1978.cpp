/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0201/1978/
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
	int a, b, c, s;
	cin >> a >> b >> c >> s;

	a %= 23;
	b %= 28;
	c %= 33;

	// while (a != b || b != c || a != c) {
	// 	while (a < b || a < c) a += 23;
	// 	while (b < c || b < a) b += 28;
	// 	while (c < a || c < b) c += 33;
	// }
	int d = s + 1;
	while (d % 23 != a) d++;
	while (d % 28 != b) d += 23;
	while (d % 33 != c) d += 23 * 28;
	cout << d - s << endl;
}
