extern "C" {
	#include <cstdio>
	#include <cstring>
	#include <cstdlib>
	#include <climits>
}

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

int childs[61][2];
int costs[61] = {0}, values[61] = {0}, parent[61];
int money, n;

int main(int argc, char * argv[]) {
	cin >> money >> n;
	
	memset(childs, 0, sizeof(childs));
	for (int i = 1; i <= n; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		costs[i] = a / 10, values[i] = b * a / 10, parent[i] = c;
		// printf("\t\t%d\n", c);
		if (c != 0) {
			if (childs[c][0]) childs[c][1] = i;
			else childs[c][0] = i;
		}
	}
	
	money /= 10;
	// printf("money = %d\n", money);
	
	
	static int dp[3201] = {0};
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= n; i++) {
		if (parent[i] == 0) {
			// printf("costs[%d] = %d\n", i, costs[i]);
			for (int v = money; v >= costs[i]; v--) {
				int ci = childs[i][0];
				int ci2 = childs[i][1];
				// printf("ci, ci2 : %d, %d\nOrigin: %d, ", ci, ci2, dp[v]);
				
				if (dp[v] <= dp[v - costs[i]] + values[i]) {
					dp[v] = dp[v - costs[i]] + values[i];
				}
				
				
				// first
				if (ci != 0 && v >= costs[i] + costs[ci])
					dp[v] = max(dp[v], dp[v - costs[i] - costs[ci]] + values[i] + values[ci]);
					
				// second
				if (ci2 != 0 && v >= costs[i] + costs[ci2])
					dp[v] = max(dp[v], dp[v - costs[i] - costs[ci2]] + values[i] + values[ci2]);
					
				// two
				if (ci2 != 0 && ci != 0 && v >= costs[i] + costs[ci] + costs[ci2])
					dp[v] = max(dp[v], dp[v - costs[i] - costs[ci] - costs[ci2]] + values[i] + values[ci2] + values[ci]);
					
				// printf("Then %d to %d\n", v, dp[v]);
			}
		}
	}
	cout << dp[money] * 10 << endl;
	return 0;
}