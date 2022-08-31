/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1005
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

#warning 这种贪心的思路是错的，啊啊啊，

typedef struct ha {
	int n[41];
} ha;

ha base, result;

int positions[80][2] = {0};
int nums[80][80] = {0};

void printNum(ha & x) {
	int i = 40;
	while (x.n[--i] == 0 && i > 0);

	while (i >= 0) {
		putchar(x.n[i--] + '0');
	}
	putchar('\n');
}

ha mul(ha & a, int x) {
	ha r;
	memset(r.n, 0, sizeof(int) * 40);

	for (int i = 0; i < 40; i++) {
		r.n[i] += a.n[i] * x;
		r.n[i + 1] += r.n[i] / 10;
		r.n[i] %= 10;
	}

	printf("\tMul base and %d to: ", x);
	printNum(r);
	return r;
}

void add(ha & a, ha & b) {
	for (int i = 0; i < 40; i++) {
		a.n[i] += b.n[i];
		a.n[i + 1] += a.n[i] / 10;
		a.n[i] %= 10;
	}

	printf("\tAdd a and b to: ");
	printNum(a);
}

void updatebase() {
	for (int i = 0; i < 40; i++) {
		base.n[i] <<= 1;
	}

	for (int i = 0; i < 40; i++) {
		base.n[i + 1] += base.n[i] / 10;
		base.n[i] %= 10;
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		positions[i][0] = 0;
		positions[i][1] = m - 1;

		for (int j = 0; j < m; j++) {
			cin >> nums[i][j];
		}
	}

	memset(base.n, 0, sizeof(int) * 40);
	memset(result.n, 0, sizeof(int) * 40);

	base.n[0] = 2;
	for (int c = 0; c < m; c++) {
		printf("base is: ");
		printNum(base);
		for (int i = 0; i < n; i++) {
			if (nums[i][positions[i][0]] < nums[i][positions[i][1]]) {
				ha tmp = mul(base, nums[i][positions[i][0]++]);
				add(result, tmp);
			} else {
				ha tmp = mul(base, nums[i][positions[i][1]--]);
				add(result, tmp);
			}
		}
		updatebase();
	}
	printNum(result);

	return 0;
}
