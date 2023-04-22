#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 2e5 + 7;

class MergeFindSet {
private:
    int grp[N];
public:
    inline void init(int n) {
        for (int i = 1; i <= n; ++i) grp[i] = i;
    }
    inline int find(int x) {
        return x == grp[x] ? x : (grp[x] = find(grp[x]));
    }
    inline int merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return grp[x] = y, 1;
        return 0;
    }
} mfs;

typedef long long lint;
int n;
int W[N], fa[N];
lint sum[N];

struct Edge {
    int to, w;
};
vector<Edge> G[N];
#define add(u, v, w) (G[(u)].push_back({(v), (w)}))

// 预处理树上信息
void prepare(int x, int p) {
    fa[x] = p;
    for (auto e : G[x]) {
        if (e.to ^ p) {
            sum[e.to] = sum[x] + e.w;
            prepare(e.to, x);
        }
    }
}

struct Tup {
    int x, g; lint d;
    bool operator < (const Tup & i) {
        return d < i.d;
    }
    void debug(string s) {
        cout << "{" << x << ", " << g << ", " << d << "}" << s;
    }
};

struct Info {
    Tup mt, st;
    inline void merge(const Info & i) {
        Tup li[4] = {mt, st, i.mt, i.st};
        sort(li, li + 4);
        mt = li[0];
        if (li[0].g != li[1].g) st = li[1];
        else if (li[0].g != li[2].g) st = li[2];
        else st = li[3];
    }

    void debug() {
        cout << " Info: "; mt.debug(" "), st.debug("\n");
    }
} info[N];

void workwy(int x) {
    info[x] = {{x, mfs.find(x), sum[x] + W[x]}, {0, 0, (lint)1e18}};
    for (auto e : G[x]) {
        if (fa[x] == e.to) continue;
        workwy(e.to);
        info[x].merge(info[e.to]);
        cout << "Node: " << x; info[x].debug();
    }
}

int link[N];
lint cost[N];
void worklink(int x) {
    if (x == 1) {
        info[x].mt.d -= sum[x] << 1;
        info[x].st.d -= sum[x] << 1;
    }

    auto mt = info[x].mt;
    if (info[x].mt.g == mfs.find(x)) {
        mt = info[x].st;
    }

    cost[x] = mt.d + sum[x] + W[x];
    link[x] = mt.x;

    for (auto e : G[x]) {
        if (e.to == fa[x]) continue;
        info[e.to].mt.d -= sum[e.to] << 1;
        info[e.to].st.d -= sum[e.to] << 1;
        info[e.to].merge(info[x]);
        worklink(e.to);
    }
}

int tmp
int main() {
    cin.tie(0)->sync_with_stdio(false);

    cin >> n; mfs.init(n);
    for (int i = 1; i <= n; ++i) cin >> W[i];

    for (int u, v, w, i = 1; i < n; ++i) {
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    } prepare(1, 0);

    int blocks = n;
    while (blocks > 1) {
        workwy(1);
        worklink(1);

        // TODO!!!!
        break;
    }
}