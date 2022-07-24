/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */

#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>

using namespace std;

void quick_sort(vector<char *> &nums, int l, int r) {
	if (l >= r)
		return;
	int first = l, last = r;
	char * key = nums[first];
	// printf("%p\n", key);
	while (first < last){
		// printf("%p\n", nums[last]);
		while(first < last && strcmp(nums[last], key) >= 0) {
			--last;
		}
		nums[first] = nums[last];
		// printf("%p\n", nums[first]);
		while (first < last && strcmp(nums[first], key) <= 0) {
			++first;
		}
		nums[last] = nums[first];
	}
	nums[first] = key;
	quick_sort(nums, l, first);
	quick_sort(nums, first + 1, r);
}

int main() {
	vector<const char *> strs;
	string cppline;
	getline(cin, cppline);

	char * line = (char *)cppline.c_str();
	int ls = strlen(line);
	strs.push_back(line);
	for (int i = 0; i < ls; i++) {
		if (line[i] == ' ' && line[i+1] != ' ') {
			line[i] = '\0';
			strs.push_back(&line[i+1]);
		}
	}

	// for (char* &s : strs) {
	// 	printf("%p\n", s);
	// }

	// cout << "Quick sort" << endl;
	// quick_sort(strs, 0, strs.size() - 1);
	
	// Selection sort
	int mid, n = strs.size();
	for (int i = 0; i < n - 1; ++i) {
		mid = i;
		for (int j = i + 1; j < n; ++j) {
			if (strcmp(strs[j], strs[mid]) < 0) {
				mid = j;
			} 
		}
		swap(strs[mid], strs[i]);
	}

	for (int i = 0; i < strs.size(); i++) {
		if (i > 0 && strcmp(strs[i], strs[i-1]) == 0) continue;
		cout << strs[i] << endl;
	}
}
