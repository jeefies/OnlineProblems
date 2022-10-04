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

int main(int argc, char * argv[]) {
	int k;
	scanf("%d", &k);
	for (int datai = 0; datai < k; datai++) {
		static char A[2001] = {0}, B[2001] = {0};
		memset(A, 0, sizeof(A)); memset(B, 0, sizeof(B));
		cin >> (A + 1) >> (B + 1);

		int sA = strlen(A+1), sB = strlen(B+1);

		static int dp[2001][2001] = {0};
		memset(dp, 0, sizeof(dp));
		for (int a = 1; a <= sA; a++) {
			dp[a][0] = a;
		}

		for (int b = 1; b <= sB; b++) {
			dp[0][b] = b;
		}

		for (int a = 1; a <= sA; a++) {
			for (int b = 1; b <= sB; b++) {
				// change this to target
				dp[a][b] = min(INT_MAX, dp[a-1][b-1] + 1);

				// if two are the same
				if (A[a] == B[b]) dp[a][b] = min(dp[a][b], dp[a-1][b-1]);

				// or ignore this char
				dp[a][b] = min(dp[a][b], dp[a][b-1] + 1);
				// or add a char in
				dp[a][b] = min(dp[a][b], dp[a-1][b] + 1);

				// printf("dp[%d][%d] set to %d\n", a, b, dp[a][b]);
			}
		}

		cout << dp[sA][sB] << endl;
	}
	return 0;
}
