/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1020
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

int maxStop(int * nums, int n) {
	static int canReach[100000] = {0}, count = 0;
	
	for (int i = 0; i < n; i++) {
		int r;
		for (r = 0; r < count; r++) {
			if (nums[i] > canReach[r]) {
				canReach[r] = nums[i];
				break;
			}
		}
		if (r == count) canReach[count++] = nums[i];
	}

	return count;
}

int needEqs(int * nums, int n) {
	static int canReach[100000] = {0}, count = 0;
	
	for (int i = 0; i < n; i++) {
		int r;
		for (r = 0; r < count; r++) {
			if (nums[i] <= canReach[r]) {
				canReach[r] = nums[i];
				break;
			}
		}
		if (r == count) canReach[count++] = nums[i];
	}

	return count;
}

int heights[100000];

int main() {
	int n = 0;

	while (cin >> heights[n]) n++;
	
	cout << maxStop(heights, n) << endl << needEqs(heights, n) << endl;

	return 0;
}
