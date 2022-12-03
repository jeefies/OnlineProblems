#include <cstring>
#include <iostream>

const long long N = 102, INF = 0x3F3F3F3F;
int mp[N][N];
long long dis[N][N];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int u, v, w;
    memset(dis, INF, sizeof(dis));
    memset(mp, INF, sizeof(mp));

    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        mp[u][v] = mp[v][u] = dis[u][v] = dis[v][u] = std::min((long long)w, dis[u][v]);
    }

    long long ans = INF;
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i < k; ++i) {
            for (int j = 1; j < k; ++j) {
                if (i == j || j == k || k == i) continue;
                ans = std::min(ans, dis[i][j] + mp[j][k] + mp[k][i]);
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
        }
    }

    if (ans != INF) std::cout << ans << std::endl;
    else std::cout << "No solution." << std::endl;
    return 0;
}