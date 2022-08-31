/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1009
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

const int MAX_SIZE = 10;
const int MAX_VAL = 1e7;

class ha {
public:
	int n[MAX_SIZE];
	ha() { memset(n, 0, sizeof(n)); }
	void iadd(ha & x) {
		for (int i = 0; i < MAX_SIZE; i++) {
			n[i] += x.n[i];
			n[i + 1] += n[i] / MAX_VAL;
			n[i] %= MAX_VAL;
		}
	}

	void imul(int x) {
		for (int i = 0; i < MAX_SIZE; i++) {
			n[i] *= x;
		}
		for (int i = 0; i < MAX_SIZE; i++) {
			n[i + 1] += n[i] / MAX_VAL;
			n[i] %= MAX_VAL;
		}
	}

	void print() {
		int i = MAX_SIZE;
		while (n[--i] == 0 && i > 0);
		
		// 第一个数不能有前导0
		printf("%d", n[i--]);

		while (i >= 0) {
			printf("%07d", n[i--]);
		}
		putchar('\n');
	}
};

int main() {
	ha result, base;
	base.n[0] = 1;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		base.imul(i + 1);
		result.iadd(base);
	}

	result.print();
	
	return 0;
}
