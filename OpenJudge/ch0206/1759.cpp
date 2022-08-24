#include <iostream>

using namespace std;

int nums[1002] = {0};
// dp[i] 表示以nums[i]结尾的最长子序列的长度
int dp[1002] = {0};

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	int maxn = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (nums[j] < nums[i])
				dp[i] = max(dp[i], dp[j] + 1);
		}
			
		maxn = max(dp[i], maxn);
	}

	printf("%d\n", maxn + 1);
}
