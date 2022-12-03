#include <iostream>
#include <cstring>

const int N = 200 + 2, M = N * N;
struct Edge {
    int to, next;
};

class Graph {
private:
    Edge edge[M];
    int head[N], tot;
    int color[N];
    int vis[N];
public:
    int n;

    Graph() {
        tot = 0;
    }

    void add(int u, int v) {
        ++tot;
        edge[tot] = {v, head[u]}, head[u] = tot;
    }

    void mark(int i, int c) {
        color[i] = c;
        vis[i] = true;
        for (int t = head[i]; t; t = edge[t].next) {
            if (!vis[edge[t].to]) mark(edge[t].to, c);
        }
    }

    void mark() {
        for (int i = 1; i <= n; ++i) {
            memset(vis, 0, sizeof vis);
            if (!color[i]) mark(i, i);
        }
    }

    int count() {
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            if (color[i] == i) ++cnt;
        }
        return cnt;
    }
};

int main() {
    static Graph g;
    scanf("%d", &g.n);
    int t;
    for (int i = 1; i <= g.n; ++i) {
        while (true) {
            scanf("%d", &t);
            if (t) g.add(i, t);
            else break;
        }
    }

    g.mark();
    std::cout << g.count() << '\n';
}