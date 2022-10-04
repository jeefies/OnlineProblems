#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int n;
int mp[10][10] = {0};
int cache[10][10][10][10];

int cdfs(int a, int b, int x, int y) {
    if (a == n - 1 && b == n - 1 && x == n - 1 && y == n - 1)
        return mp[n - 1][n - 1];

    if (a >= n || b >= n || x >= n || y >= n) return 0;

    if (cache[a][b][x][y] >= 0) return cache[a][b][x][y];

    int oab = mp[a][b];
    // prevent from getting the same place, and prevent second search
    mp[a][b] = 0;
    int cur = oab + mp[x][y];
    int best = 0;

    if (b + 1 < n && y + 1 < n) best = max(best, cdfs(a, b + 1, x, y + 1) + cur);
    if (b + 1 < n && x + 1 < n) best = max(best, cdfs(a, b + 1, x + 1, y) + cur);
    if (a + 1 < n && y + 1 < n) best = max(best, cdfs(a + 1, b, x, y + 1) + cur);
    if (a + 1 < n && x + 1 < n) best = max(best, cdfs(a + 1, b, x + 1, y) + cur);

    // backtrace
    mp[a][b] = oab;
    cache[a][b][x][y] = best;
    return best;
}

int main(int argc, char const *argv[]) {
    memset(cache, 0xF0, sizeof(cache));

    scanf("%d", &n);
    int x, y, n;
    while (scanf("%d%d%d", &x, &y, &n)) {
        if (x + y + n == 0) break;
        mp[x - 1][y - 1] = n;
    }

    printf("%d\n", cdfs(0, 0, 0, 0));
    return 0;
}
