#include <iostream>
#include <stack>
#include <vector>
#include <set>

using std::stack;
using std::set;

const int N = 3000 + 2, M = 8000 + 2, INF = 0x3F3F3F3F;

struct Edge {
    int next, to;
};

int col[N], vis[N], dfn[N], low[N], cdfn = 0, cnt = 0;
set<int> grp[N];
static int canBuy[N];

class Graph {
private:
    int head[N], tot;
    struct Edge edge[M];
public:
    int n;
    Graph() : tot(0) {
        for (int i = 1; i < N; ++i) canBuy[i] = INF;
    };

    void add(int u, int v) {
        edge[++tot] = {head[u], v}, head[u] = tot;
    }

    void tarjan(int x, stack<int> &stk) {
        dfn[x] = low[x] = ++cdfn;
        vis[x] = true, stk.push(x);

        for (int i = head[x]; i; i = edge[i].next) {
            int y = edge[i].to;
            if (!dfn[y]) {
                tarjan(y, stk);
                low[x] = std::min(low[x], low[y]);
            } else if (vis[y]) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }

        if (dfn[x] == low[x]) {
            ++cnt;
            int t;
            do {
                t = stk.top(); stk.pop();
                vis[t] = false, col[t] = cnt;
                grp[cnt].insert(t);
            } while (t != x);
        }
    }

    void tarjan() {
        stack<int> stk;
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) tarjan(i, stk);
        }
    }

    void shrinkIT(int * it) {
        for (int x = 1; x <= n; ++x) {
            for (int i = head[x]; i; i = edge[i].next) {
                int y = edge[i].to;
                if (col[x] != col[y]) ++it[col[y]];
            }
        }
    }
};

int main() {
    static Graph g;

    int n;
    scanf("%d", &n);
    g.n = n;

    int p;
    scanf("%d", &p);
    int a, c;
    for (int i = 0; i < p; ++i) {
        scanf("%d %d", &a, &c);
        canBuy[a] = c;
    }

    int m;
    scanf("%d", &m);
    int u, v;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &u, &v);
        g.add(u, v);
    }
    g.tarjan();

    static int it[N];
    g.shrinkIT(it);

    int cost = 0;
    for (int i = 1; i <= cnt; ++i) {
        if (it[i] == 0) {
            // we should buy it
            int delta = INF;
            for (const int &j : grp[i]) {
                delta = std::min(delta, canBuy[j]);
            }
            if (delta == INF) {
                printf("NO\n%d\n", *grp[i].begin());
                return 0;
            }
            cost += delta;
        }
    }
    printf("YES\n%d\n", cost);
    return 0;
}