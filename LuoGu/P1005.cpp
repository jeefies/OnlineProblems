/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1005
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

// high accuracy
// 高精度类
class ha {
public:
	int n[41];

	// 构造器，创建时清零，防止出现乱七八糟的东西
	ha() {
		memset(n, 0, sizeof(n));
	}

	// 主要是为了把int转换为高精度数
	ha add(int b) {
		ha r;
		r.n[0] = b;
		int i = 0;
		while (r.n[i] != 0) {
			r.n[i] += n[i];
			r.n[i + 1] += r.n[i] / 10;
			r.n[i++] %= 10;
		}
		return r;
	}

	ha add(ha b) {
		ha r;
		for (int i = 0; i < 40; i++) {
			r.n[i] += n[i] + b.n[i];
			r.n[i + 1] += r.n[i] / 10;
			r.n[i] %= 10;
		}
		return r;
	}

	ha mul(int x) {
		ha r;
		for (int i = 0; i < 40; i++) {
			r.n[i] = n[i] * x;
		}

		for (int i = 0; i < 40; i++) {
			r.n[i + 1] += r.n[i] / 10;
			r.n[i] %= 10;
		}
		return r;
	}

	// 默认参数，不要在意这个语法
	void print(bool newline = true) {
		int i = 40;
		while (n[--i] == 0 && i > 0);

		while (i >= 0)
			putchar(n[i--] + '0');

		if (newline) putchar('\n');
	}
};

// 重载max对于高精度数的函数
ha max(ha a, ha b) {
	for (int i = 40; i >= 0; i--) {
		if (a.n[i] > b.n[i]) return a;
		else if (a.n[i] < b.n[i]) return b;
	}

	return a;
}

ha nums[80], result;

/*
ha lineMax(ha * ns, int m) {
	// 使用static数组，减少空间创建与释放
	static ha dp[80][80];
	// 由于使用的是static数组，所以每一次也要清零才能继续
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i < m; i++) {
		dp[i][i] = dp[i][i].add(ns[i]);
		printf("DP[%d][%d] set to: ", i, i); dp[i][i].print();
	}

	for (int len = 2; len <= m; len++) {
		for (int i = 0, j = len - 1; j < m; i++, j++) {
			// 这么多printf是用来调试的，请勿在意
			printf("At DP[%d][%d]:\n", i, j);

			printf("\tns[%d]: ", i); ns[i].print(false);
			printf("  ns[%d]: ", j); ns[j].print();

			// 分两行写好看一点^_^
			dp[i][j] = max(
					ns[i].add(dp[i + 1][j].mul(2)), 
					ns[j].add(dp[i][j - 1].mul(2))
				);

			printf("\tDP[%d][%d] set to: ", i, j); dp[i][j].print();
		}
	}

	return dp[0][m - 1].mul(2);
}
*/

ha lineMax(ha * ns, int m) {
	ha * dp = new ha[m];
	for (int i = 0; i < m; i++) {
		dp[i] = dp[i].add(ns[i]);
	}

	for (int len = 1; len < m; len++) {
		for (int i = 0; i < m - i; i++)
			dp[i] = max(
					ns[i].add(dp[i + 1].mul(2)),
					ns[i + len].add(dp[i].mul(2))
				);
	}

	return dp[0].mul(2);
}

int main() {
	int n, m;
	cin >> n >> m;

	ha result;

	for (int i = 0; i < n; i++) {
		// 每一都要清零
		memset(nums, 0, sizeof(nums));

		int tmp;
		for (int j = 0; j < m; j++) {
			cin >> tmp;
			nums[j] = nums[j].add(tmp);
		}

		ha lm = lineMax(nums, m);
		// printf("line %d add max: ", i); lm.print();
		result = result.add(lm);
	}

	result.print();

	return 0;
}
