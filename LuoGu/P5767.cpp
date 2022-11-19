#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

const int M = 100, N = 500, INF = 0x3F3F3F3F;
int mp[N][N];

int main() {
	memset(mp, 0x3F, sizeof(mp));
	
	int m, n;
	scanf("%d %d", &m, &n);
	
	string line;
	static int a[N];
	for (int i = 0; i < m; i++) {
		char tmp;
		int k, cnt = 0;
		while (true) {
			scanf("%d", &k);
			a[cnt++] = k;
			if (getchar() != ' ') break;
		}
		
		for (int i = 0; i < cnt; i++) {
			for (int j = i + 1; j < cnt; j++)
				mp[a[i]][a[j]] = 1;
		}
	}
	
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
			}
	}
	
	if (mp[1][n] != INF) cout << mp[1][n] - 1 << endl;
	else cout << "NO" << endl; 
}
