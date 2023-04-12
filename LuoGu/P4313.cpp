#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 100 + 3, M = (N * N) << 2, INF = 0x7FFFFFFF;

// max nodes n * m + n * m;
int n, m, s, t;
inline int flat(int x, int y) {
    return (x - 1) * m + y;
}

struct Edge {
    int to, next, flow;
} edge[M];
int head[M], usage = 1;

inline void add(int u, int v, int f) {
    edge[++usage] = {v, head[u], f}, head[u] = usage;
}
inline void addflow(int u, int v, int f) {
    printf("%d %d %d\n", u, v, f);
    add(u, v, f), add(v, u, 0);
}

int dep[M], gap[M];
int q[M];
void isapInit() {
    fill(dep, dep + t + 1, -1);
    gap[(dep[t] = 0)] = 1;

    int qhead = 0, qtail = 0;
    q[qtail++] = t;
    while (qhead ^ qtail) {
        int x = q[qhead++];
        for (int y, i = head[x]; i; i = edge[i].next) {
            if (dep[(y = edge[i].to)] == -1)
                q[qtail++] = y, ++gap[(dep[y] = dep[x] + 1)];
        }
    } // end bfs
}

inline int sap(int x, int flow) {
    if (x == t) return flow;

    int rest = flow;
    for (int y, i = head[x]; i; i = edge[i].next) {
        if ((dep[(y = edge[i].to)] + 1) != dep[x] || !edge[i].flow) continue;
        int f = sap(y, min(flow, edge[i].flow));
        if (f) {
            edge[i].flow -= f, edge[i ^ 1].flow += f;
            rest -= f;
        }
        if (!rest) return flow;
    }

    if (--gap[dep[x]] == 0) dep[s] = t + 1;
    return ++gap[++dep[x]], flow - rest;
}

int main() {
    freopen("test.out", "w", stdout);

    // cin.tie(0)->sync_with_stdio(false);

    cin >> n >> m;
    int sum = 0;
    int fakeStart = flat(n, m);
    s = 0, t = fakeStart + n * m * 2 + 1;
    for (int x, i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> x, sum += x;
            addflow(0, flat(i, j), x);
        }
    }

    for (int x, i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> x, sum += x;
            addflow(flat(i, j), t, x);
        }
    }

    for (int x, i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> x, sum += x;
            addflow(s, ++fakeStart, x);
            addflow(fakeStart, flat(i, j), INF);
            if (i > 1) addflow(fakeStart, flat(i - 1, j), INF);
            if (j > 1) addflow(fakeStart, flat(i, j - 1), INF);
            if (i < n) addflow(fakeStart, flat(i + 1, j), INF);
            if (j < m) addflow(fakeStart, flat(i, j + 1), INF);
        }
    }

    for (int x, i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> x, sum += x;
            addflow(++fakeStart, t, x);
            addflow(flat(i, j), fakeStart, INF);
            if (i > 1) addflow(flat(i - 1, j), fakeStart, INF);
            if (j > 1) addflow(flat(i, j - 1), fakeStart, INF);
            if (i < n) addflow(flat(i + 1, j), fakeStart, INF);
            if (j < m) addflow(flat(i, j + 1), fakeStart, INF);
        }
    }

    isapInit();
    int maxflow = 0;
    while (dep[s] <= t) {
        cout << "dep: " << dep[s] << '\n';
        maxflow += sap(s, INF);
    }
    cout << maxflow << '\n';
    cout << sum - maxflow << '\n';
    return 0;
}