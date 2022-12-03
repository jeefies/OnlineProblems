#include <iostream>

struct Edge {
    int next, to;
};

const int N = 6e4 + 2, M = 5e4 + 2;

class Graph {
private:
    int head[N], tot;
    Edge edge[M];
public:
    int n;

    void add(int u, int v) {
        edge[++tot] = {head[u], v}, head[u] = tot;
    }

    int match[N], vis[N], tag;
    bool dfs(int x) {
        for (int i = head[x]; i; i = edge[i].next) {
            int y = edge[i].to;
            
            // 已经匹配过了，不能匹配
            if (vis[y] == tag) continue; 
            // 保证y不会在递归中被再次匹配
            vis[y] = tag;

            // y没有被匹配过，直接与x匹配
            if (!match[y]) {
                match[y] = x;
                return true;
            }

            // 尝试重新匹配y
            if (dfs(match[y])) {
                // y原所匹配的重新匹配到了另一个点，y现在可以与x匹配
                match[y] = x;
                return true;
            }
            // y重新匹配失败，需要换一个y再次匹配
        }
        // 匹配失败，x无法再匹配了 T^T
        return false;
    }

    int maxMatch() {
        int mc = 0;
        for (int i = 1; i <= n; ++i) {
            tag = i;
            if (dfs(i)) ++mc;
        }


        // printf("n: %d\n", n);
        // for (int i = 1; i <= n; ++i) printf("%d ", match[i]);
        // printf("\n");

        return mc;
    }
};

int main() {
    static Graph g;

    int m, e;
    scanf("%d %d %d", &g.n, &m, &e);

    for (int i = 0, u, v; i < e; ++i) {
        scanf("%d %d", &u, &v);
        g.add(u, v + e);
    }

    std::cout << g.maxMatch() << std::endl;
}