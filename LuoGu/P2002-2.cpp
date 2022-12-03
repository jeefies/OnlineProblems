#include <stack>
#include <cstring>
#include <iostream>

const int N = 1e5 + 2, M = 5e5 + 3;

int col[N], cnt = 0;

class Graph {
private:
    int head[N], rhead[N], tot;
    struct Edge {
        int next, to;
    } edge[M], redg[M];

    int vis[N];
public:
    int n;
    void add(int u, int v) {
        edge[++tot] = {head[u], v}, head[u] = tot;
        redg[tot] = {rhead[v], u}, rhead[v] = tot;
    }

    void kosaraju(int i, int mark) {
        vis[i] = true, col[i] = mark;
        for (int t = rhead[i]; t; t = redg[t].next) {
            int to = redg[t].to;
            if (!vis[to])
                kosaraju(to, mark);
        }
    }

    void kosaraju(int i, std::stack<int> &stk) {
        vis[i] = true;
        for (int t = head[i]; t; t = edge[t].next) {
            if (!vis[edge[t].to])
                kosaraju(edge[t].to, stk);
        }
        stk.push(i);    
    }

    int kosaraju() {
        cnt = 0;
        memset(vis, 0, sizeof(vis));
        std::stack<int> stk;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) kosaraju(i, stk);
        }
        memset(vis, 0, sizeof(vis));
        while (stk.size()) {
            int s = stk.top(); stk.pop();
            if (!vis[s]) kosaraju(s, ++cnt);
        }
    }

    int shrink_0in() {
        memset(vis, 0, sizeof(vis));
        for (int x = 1; x <= n; ++x) {
            for (int t = head[x]; t; t = edge[t].next) {
                int y = edge[t].to;
                if (col[x] != col[y]) ++vis[col[y]];
            }
        }

        int ans = 0;
        for (int i = 1; i <= cnt; ++i) {
            if (!vis[i]) ++ans;
        }
        return ans;
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    static Graph g;
    g.n = n;

    int u, v;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &u, &v);
        g.add(u, v);
    }

    g.kosaraju();
    std::cout << g.shrink_0in() << std::endl;
    return 0;
}