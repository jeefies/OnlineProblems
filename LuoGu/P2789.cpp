#include <iostream>
#include <set>

bool dp[30][400];

int main() {
	int n, ans, m;
    scanf("%d", &n);
    m = (n - 1) * n / 2;
    for (int i = 1; i <= n; ++i) dp[i][0] = true;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; j++)
            for (int k = 1; k <= n - i; k++)
                dp[i + k][j + k*i] |= dp[i][j];
    for (int i = 0; i <= m; i++)
        if (dp[n][i]) ans++;
    printf("%d", ans);
    return 0;
}
