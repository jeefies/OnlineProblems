/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1021
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

int kinds[15], ki = 1;
bool canReach[1000] = {false};
char reachNeed[1000] = {0};


void search(int n, int k, int from) {
	// 
}

int main() {
	int n, k;
	cin >> n >> k;

	kinds[1] = 1;

	for (int i = 1; i <= n; i++) {
		canReach[i] = true;
		reachNeed[i] = i;
	}

	search(n, k - 1, n + 1, 1);
}
