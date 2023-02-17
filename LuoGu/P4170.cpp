#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 50 + 7, INF = 0x3F3F3F3F;

int n;
char s[N];

void read() {
	scanf("%s", s);
	n = strlen(s);
}

static int dp[N][N];
void work() {
	for (int i = 0; i < n; ++i) {
		dp[i][0] = 1;
	}
	
	for (int l = 1; l < n; ++l) {
		for (int i = 0; i + l < n; ++i) {
			if (s[i] == s[i + l])
				dp[i][l] = min(dp[i][l - 1], dp[i + 1][l - 1]);
			else {
				dp[i][l] = INF;
				for (int k = 0; k <= l; k++)
					dp[i][l] = min(dp[i][l], dp[i][k] + dp[i + k + 1][l - k - 1]);
			}
		}
	}
}

int main() {
	read();
	work();
	printf("%d\n", dp[0][n - 1]);
	return 0;
}
