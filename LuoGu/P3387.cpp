#include <stack>
#include <cstring>
#include <iostream>

using namespace std;

struct Edge {
    int next, to;
};

const int N = 1e4 + 2, M = 1e5 + 2;
static int col[N] = {0}, dfn[N] = {0}, low[N] = {0}, vis[N] = {0}, cnt = 0, cdfn = 0;
class Graph {
public:
    int n;
    int head[N], tot;
    Edge edge[M];
    int a[N];

    void add(int u, int v) {
        ++tot;
        edge[tot] = {head[u], v}, head[u] = tot;
    }

    void tarjan(int x, stack<int> &stk) {
        // printf("Tarjan in %d\n", x);
        dfn[x] = low[x] = ++cdfn;
        vis[x] = true, stk.push(x);

        for (int i = head[x]; i; i = edge[i].next) {
            int y = edge[i].to;
            if (!dfn[y]) {
                tarjan(y, stk);
                low[x] = min(low[x], low[y]);
            } else if (vis[y]) {
                low[x] = min(low[x], dfn[y]);
            }
            // printf("\tTo %d, low[%d] changed to %d\n", y, x, low[x]);
        }

        if (dfn[x] == low[x]) {
            int top;
            ++cnt;
            do {
                top = stk.top(); stk.pop();
                vis[top] = false, col[top] = cnt;
            } while (top != x);
        }
    }

    Graph& tarjan() {
        static Graph shrink;
        stack<int> stk;
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) tarjan(i, stk);
        }

        // printf("graph n = %d\n", n);
        for (int i = 1; i <= n; ++i) {
            shrink.a[col[i]] += a[i];
            // printf("%d ", col[i]);
        }
        // printf("\n");
        shrink.n = cnt;

        for (int x = 1; x <= n; ++x) {
            for (int t = head[x]; t; t = edge[t].next) {
                int y = edge[t].to;
                if (col[x] != col[y]) {
                    shrink.add(col[x], col[y]);
                }
            }
        }
        return shrink;
    }

    int dfs(int i) {
        static int cache[N];

        if (cache[i]) return cache[i];

        int w = 0;
        for (int t = head[i]; t; t = edge[t].next) {
            w = max(w, dfs(edge[t].to));
        }
        w += a[i];
        return cache[i] = w;
    }
};

static Graph g;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    g.n = n;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", g.a + i);
    }

    int u, v;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        g.add(u, v);
    }

    Graph &shrink = g.tarjan();
    int ans = 0;
    for (int i = 1; i <= cnt; ++i) {
        ans = max(ans, shrink.dfs(i));
    }

    std::cout << ans << std::endl;
}