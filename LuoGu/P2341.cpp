#include <iostream>
#include <stack>

using std::stack;

const int N = 1e4 + 2, M = 5e4 + 1;

struct Edge {
    int next, to;
};

int col[N], vis[N], dfn[N], low[N], cdfn = 0, cnt = 0;

class Graph {
private:
    int head[N], tot;
    Edge edge[M];
public:
    int n;
    Graph() : tot(0) {}

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
            // printf("Group add\n");
            ++cnt;
            int t;
            do {
                t = stk.top(); stk.pop();
                vis[t] = false, col[t] = cnt;
            } while (t != x);
        }
    }

    void tarjan() {
        stack<int> stk;
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) tarjan(i, stk);
        }
    }

    int countStars() {
        static int ot[N];
        for (int x = 1; x <= n; ++x) {
            for (int i = head[x]; i; i = edge[i].next) {
                int y = edge[i].to;
                if (col[x] != col[y]) {
                    ++ot[col[x]];
                }
            }
        }

        int starsCount = 0, starGrp;
        for (int g = 1; g <= cnt; ++g) {
            if (ot[g] == 0) ++starsCount, starGrp = g;
        }

        if (starsCount != 1) return 0;
        // remember here starsCount is 1
        for (int x = 1; x <= n; ++x) {
            if (col[x] == starGrp) ++starsCount;
        }
        return starsCount - 1;
    }
};

int main() {
    static Graph g;
    int m;
    scanf("%d %d", &g.n, &m);
    int u, v;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        g.add(u, v);
    }
    g.tarjan();
    std::cout << g.countStars() << std::endl;
}