#include <stack>
#include <iostream>
#include <cstring>

struct Edge {
    int next, to;
};

const int N = 202, M = 40000;

int dfn[N], low[N], ins[N], col[N], cdfn = 0, cnt = 0;
std::stack<int> stk;

class Graph {
private:
public:
    int head[N], tot;
    Edge edge[M];
    int n;

    Graph() {
        tot = 0;
    }

    void add(int u, int v) {
        edge[++tot] = {head[u], v}, head[u] = tot;
    }

    void tarjan() {
        memset(ins, 0, sizeof(ins));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) tarjan(i);
        }
    }

    void tarjan(int x) {
        dfn[x] = low[x] = ++cdfn;
        ins[x] = true; stk.push(x);

        for (int i = head[x]; i; i = edge[i].next) {
            int y = edge[i].to;
            if (!dfn[y]) {
                tarjan(y);
                low[x] = std::min(low[x], low[y]);
            } else if (ins[y]) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }

        if (dfn[x] == low[x]) {
            ++cnt;
            int top;
            do {
                top = stk.top(); stk.pop();
                ins[top] = false, col[top] = cnt;
            } while (top != x);
        }
    }
};

int main() {
    static Graph g;
    scanf("%d", &g.n);
    for (int i = 1; i <= g.n; ++i) {
        int t;
        while (true) {
            scanf("%d", &t);
            if (t) g.add(i, t);
            else break;
        }
    }

    g.tarjan();
    
    static int it[N] = {0};
    for (int x = 1; x <= g.n; ++x) {
        for (int i = g.head[x]; i; i = g.edge[i].next) {
            int y = g.edge[i].to;
            if (col[x] != col[y]) {
                ++it[col[y]];
            }
        }
    }
    int ans = 0;
    for (int x = 1; x <= cnt; ++x) {
        if (it[x] == 0) ++ans;
    }

    std::cout << ans << std::endl;
}