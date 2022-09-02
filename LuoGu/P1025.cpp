/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1025
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

int search(int n, int k, int start) {
	if (n < start) return 0;
	if (k-- == 1) return 1;

	int cnt = 0;
	for (int i = start; i <= n - k * start; i++) {
		cnt += search(n - i, k, i);
	}

	return cnt;
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	printf("%d\n", search(n, k, 1));
}
