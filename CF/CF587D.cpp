#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
const int N = 1e5 + 3;

struct Edge {
    int to, w, c, i;
    bool operator < (const Edge &e) {
        return c < e.c;
    }
};
vector<Edge> G[N];

int n, m, mw = 0;
void read() {
    cin >> n >> m;
    int u, v, w, c, p = 0;
    map<int, int> mp;
    for (int i = 1; i <= m; ++i) {
        cin >> u >> v >> w >> c;
        mw = max(mw, w);
        if (!mp[c]) mp[c] = ++p;
        G[u].push_back({v, w, c, i});
        G[v].push_back({u, w, c, i});
    }
    
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    read();

    // check for valid
    for (int x = 1; x <= n; ++x) {
        cout << "At node " << x << '\n';
        sort(G[x].begin(), G[x].end());
        for (auto e : G[x]) {
            cout << "\t" << e.u << " " << e.v << 
        }
        for (int i = 2, ie = G[x].size(); i < ie; ++i)
            if (G[x][i].c == G[x][i - 2].c) return puts("No"), 0;
    }
}