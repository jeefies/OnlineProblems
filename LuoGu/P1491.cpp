#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;
const int N = 207;

struct Edge {
    int to;
    double w;
};
vector<Edge> G[N];
inline void add(int u, int v, double w) {
    G[u].push_back({v, w});
    G[v].push_back({u, w});
}

double px[N], py[N];
struct Node {
    int x;
    double w;
    bool operator < (const Node &n) const {
        return w > n.w;
    }
};

vector<int> vis;
void djk(int s, int bx, int by, double * dis, int * pre) {
    // cout << "DJK block " << bx << " " << by << '\n';
    vis.assign(N, 0);
    priority_queue<Node> q;
    q.push({s, (dis[s] = 0)});

    while (q.size()) {
        auto node = q.top(); q.pop();
        if (vis[node.x]) continue;
        vis[node.x] = true;
        for (auto e : G[node.x]) {
            if (vis[e.to]) continue;
            if ((bx == node.x && by == e.to) || (by == node.x && bx == e.to)) continue;
            if (dis[e.to] > dis[node.x] + e.w) {
                dis[e.to] = dis[node.x] + e.w;
                pre[e.to] = node.x;
                q.push({e.to, dis[e.to]});
            }
        }
    }
}

int pre[N], tmp[N];
double dis[N];
int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> px[i] >> py[i];
    }

    for (int u, v, i = 1; i <= m; ++i) {
        cin >> u >> v;
        double d = ({
            double dx = px[u] - px[v], dy = py[u] - py[v];
            sqrt(dx * dx + dy * dy);
        }); add(u, v, d);
    }

    fill(dis, dis + 1 + n, 2e9);
    djk(1, 0, 0, dis, pre);
    for (int i = 1; i <= n; ++i) {
        // cout << "Node " << i << " dis, pre = " << dis[i] << ' ' << pre[i] << '\n';
    }

    double sec = 2e9;
    for (int c = n; c != 1; c = pre[c]) {
        fill(dis, dis + 1 + n, 2e9);
        djk(1, c, pre[c], dis, tmp);
        sec = min(sec, dis[n]);
    }
    printf("%.2lf\n", sec);
    return 0;
}