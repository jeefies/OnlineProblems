#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
采用动态数组搜索，思路与2类似 
*/

const int N = 1e5 + 2;
vector<int> mp[N];
static int vis[N] = {0};

int dfs(int org, int big) {
	if (vis[org]) return vis[org];
	vis[org] = big;
	for (int i = 0; i < mp[org].size(); i++) {
		if (!vis[mp[org][i]]) dfs(mp[org][i], big);
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	int u, v;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		mp[v].push_back(u);
	}
	
	for (int i = n; i >= 1; i--) dfs(i, i);
	for (int i = 1; i <= n; i++) printf("%d ", vis[i]);
	return 0;
}
