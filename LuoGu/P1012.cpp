/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1012
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

bool cmp(string & a, string & b) {
	return a + b > b + a;
}

int main() {
	int n;
	cin >> n;

	string * nums = new string[n];
	
	for (int i = 0; i < n; i++)
		cin >> nums[i];
	
	sort(nums, nums + n, cmp);
	
	for (int i = 0; i < n; i++)
		cout << nums[i];
	
	delete[]nums;
}
