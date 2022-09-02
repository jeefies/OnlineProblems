/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1014
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
	int target;
	cin >> target;

	int current = 1, up = 1, down = 1, adder = -1, loopCount = 0;
	while (current < target) {
		++loopCount;
		adder = -adder;

		++current;
		if (adder > 0) ++down;
		else ++up;

		for (int i = 0; i < loopCount && current < target; ++i, ++current) {
			up += adder;
			down -= adder;
		}
	}

	printf("%d/%d\n", up, down);

	return 0;
}
