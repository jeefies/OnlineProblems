#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 12;
// dp[i][j] 在第i位填数字j有多少种情况 位从右向左 
// 保证 i-1 位可以填满 
int dp[N][N];
// dp[i][j] = dp[i - 1][k] (abs(j - k) >= 2)

void init() {
	for (int j(0); j < 10; ++j)
		dp[0][j] =  1;
		
	for (int i(1); i < N; ++i) {
		for (int j(0); j < 10; ++j) {
			for (int k(0); k < 10; ++k) if (abs(j - k) >= 2)
				dp[i][j] += dp[i - 1][k];
		}
	}
}

int solve(int x) {
	if (!x) return 0;
	
	static int n[N];
	int len(0), ans(0);
	while (x) {
		n[len++] = x % 10, x /= 10;
	} --len;
	
	// 考虑最高位为0的情况
	// 也就是说求长度小于 len 的情况 
	for (int i(0); i < len; ++i) {
		for (int j(0); j < 10; ++j)
			ans += dp[i][j];
	}
	
	// 考虑最高位没有达到上界 
	for (int j(1); j < n[len]; ++j) {
		ans += dp[len][j];
	}
	
	// 最高位达到上线
	for (int i = len - 1; i >= 0; --i) {
		// 考虑 i 位没有达到上线
		for (int j(0); j < n[i]; ++j) {
			//  如果与 i + 1 位相差满足要求才加 
			if (abs(j - n[i + 1]) >= 2) ans += dp[i][j]; 
		}
		if (abs(n[i] - n[i + 1]) < 2) break; // 转移不可行了？？？？？ 
	} 
}

int main() {
	int l, r;
	scanf("%d %d", &l, &r);
	printf("%d\n", solve(r) - solve(l - 1));
	return 0;
}
