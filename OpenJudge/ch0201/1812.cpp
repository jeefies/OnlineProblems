/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0201/1812/
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
	int a, b, c, d;

	int n;
	cin >> n;

	for (a = 2; a <= n; a++) {
		for (b = 2; b < a; b++) {
			for (c = b; c < a; c++) {
				for (d = c; d < a; d++) {
					if (a * a * a == b * b * b + c * c * c + d * d * d) {
						printf("Cube = %d, Triple = (%d,%d,%d)\n", a, b, c, d);
					}
				}
			}
		}
	}
}
