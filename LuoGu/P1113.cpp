#include <stdio.h>
#include <string.h>
#include <queue>

const int N = 1e5 + 2, M = 10 * N;

int head[N], size = 0, ins[N];
struct Edge {
    int next, to;
} edge[M];

void add(int u, int v) {
    ++size; edge[size].next = head[u], edge[size].to = v;
    head[u] = size, ++ins[v];
}

static int dp[N] = {0};
static int time[N];
void topsort(int n, int * order) {
    int size = 0;
    std::queue<int> q;
    for (int i = 0; i <= n; i++) {
        if (ins[i] == 0) q.push(i), dp[i] = time[i];
    }

    while (q.size()) {
        int top = q.front(); q.pop();
        order[size++] = top;

        for (int i = head[top]; i; i = edge[i].next) {
            int to = edge[i].to;
            dp[to] = std::max(dp[to], dp[top] + time[to]);
            if (--ins[to] == 0) q.push(to);
        }

    }
}

int main() {
    int n;
    scanf("%d ", &n);

    int i, j;
    for (int p = 0; p < n; p++) {
        scanf("%d %d", &i, time + p + 1);
        while (scanf("%d", &j) && j != 0) {
            add(j, i);
        }
        add(0, i);
    }

    static int order[N]; // memset(order, 0, sizeof(order));
    topsort(n, order);
    // for (int i = 0; i <= n; i++) printf("%d(%d) ", order[i], dp[i]); putchar('\n');

    int maxt = 0;
    for (int i = 0; i <= n; i++) maxt = std::max(maxt, dp[i]);
    printf("%d\n", maxt);

    return 0;
}