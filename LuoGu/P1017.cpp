/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1017
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

void changeBase(int n, int base) {
	int k = n % base;
	if (k < 0) k += -base, n += base;
	
	n /= base;
	if (n) changeBase(n, base);

	if (k > 9) putchar(k - 10 + 'A');
	else putchar(k + '0');
}

int main() {
	int n;
	cin >> n;

	int base;
	cin >> base;

	if (n == 0) printf("0=0(base=%d)\n", base);
	else { printf("%d=", n); changeBase(n, base); printf("(base%d)\n", base); }
	return 0;
}
