/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0201/1943/
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

int isvalid(int a, int b) {
	int ab = a*a + b*b;
	int c = (int)sqrt((double)ab);
	if (c <= 100 && c * c == ab)
		return c;
	return 0;
}

int main() {
	for (int a = 2; a <= 100; a++) {
		for (int b = a; b <= 100; b++) {
			int c = 0;
			if ((c = isvalid(a, b))) {
				printf("%d*%d + %d*%d = %d*%d\n", a, a, b, b, c, c);
			}
		}
	}
	return 0;
}
