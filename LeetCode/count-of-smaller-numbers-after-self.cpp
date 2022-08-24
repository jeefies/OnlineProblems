#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> countSmall(vector<int> & nums) {
		return nums;
	}
};

int main() {
	Solution slt;
	
	vector<int> tmp;
	
	tmp = slt.countSmall(vector<int>{5,2,6,1});
	for (int i = 0; i < tmp.size(); i++) {
		cout << tmp[i] << ' ';
	}
	cout << endl;
}
