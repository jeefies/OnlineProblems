#include <iostream>
#include <cstring>

using namespace std;

const int N = 2501;
int n, m, s, t;
int mp[N][N];

int main() {
	scanf("%d %d %d %d", &n, &m, &s, &t);
	int u, v, w;
	memset(mp, 0x3f, sizeof(mp));
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		mp[u][v] = mp[v][u] = w;
	}
	
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]); 
	}
	printf("%d\n", mp[s][t]);
	return 0;
}