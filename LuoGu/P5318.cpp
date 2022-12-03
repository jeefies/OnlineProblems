#include <algorithm>
#include <iostream>
#include <cstring>
#include <stack>
#include <queue>
#include <set>

using namespace std;

const int N = 1e5 + 2;

set<int> st[N];

void dfs(int s) {
    static int vis[N]; // memset(vis, 0, sizeof(vis));
    stack<int> stk; stk.push(s);

    while (stk.size()) {
        int p = stk.top(); stk.pop();
        if (vis[p]) continue;
        vis[p] = true; printf("%d ", p);
        for (auto iter = st[p].rbegin(); iter != st[p].rend(); ++iter) {
            if (!vis[*iter]) stk.push(*iter);
        }
    } putchar('\n');
}

void bfs(int s) {
    static int vis[N]; // memset(vis, 0, sizeof(vis));
    queue<int> que; que.push(s);

    while (que.size()) {
        int p = que.front(); que.pop();
        if (vis[p]) continue;
        vis[p] = true; printf("%d ", p);
        for (auto iter = st[p].begin(); iter != st[p].end(); ++iter) {
            if (!vis[*iter]) que.push(*iter);
        }
    } putchar('\n');
}

int main(int argc, char const *argv[])
{
    int n, m;
    scanf("%d %d", &n, &m);

    int x, y;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &x, &y);
        st[x].insert(y);
    }

    dfs(1);
    bfs(1);
    
    return 0;
}
