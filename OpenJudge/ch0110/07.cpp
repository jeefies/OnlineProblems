/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>

using namespace std;

void quick_sort(vector<double> &nums, int l, int r) {
	if (l >= r)
		return;
	double first = l, last = r, key = nums[first];
	while (first < last){
		while(first < last && nums[last] >= key)
			--last;
		nums[first] = nums[last];
		while (first < last && nums[first] <= key)
			++first;
		nums[last] = nums[first];
	}
	nums[first] = key;
	quick_sort(nums, l, first);
	quick_sort(nums, first + 1, r);
}

int main() {
	int pcount;

	vector<double> male;
	vector<double> female;
	cin >> pcount;

	string gender;
	double height;
	for (int i = 0; i < pcount; i++) {
		cin >> gender >> height;
		if (gender[0] == 'f') {
			female.push_back(height);
		} else {
			male.push_back(height);
		}
	}

	quick_sort(female, 0, female.size() - 1);
	quick_sort(male, 0, male.size() - 1);

	reverse(female.begin(), female.end());

	for (const double &h : male) {
		printf("%.2lf ", h);
	}

	for (const double &h : female) {
		printf("%.2lf ", h);
	}
	printf("\n");
}
