/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1008
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
#include <cstdio>

using namespace std;

class bitset {
public:
	int x;
	bitset() { x = 0; };
	void set(int i) {
		if (i)
			x |= 1 << i;
		// bool changed = true;
		// if (x & (i << i) != 0) changed = false;
		// else x |= 1 << i;
		// return changed;
	}
	// or clear
	int count() {
		int r = 0;
		while (x) {
			x -= x & -x;
			r += 1;
		}
		return r;
	}
};

int main() {
	bitset bs;
	for (int i = 111; i < 334; i++) {
		// cout << "Counting " << i << endl;
		int a = i, b = i * 2, c = i * 3;

		for (int k = 0; k < 3; k++) {
			bs.set(a % 10);
			a /= 10;
			bs.set(b % 10);
			b /= 10;
			bs.set(c % 10);
			c /= 10;
		}
		if (bs.count() == 9)
			printf("%d %d %d\n", i, i * 2, i * 3);
	}
	return 0;
}
