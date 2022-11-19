#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 2501, INF = 0x3F3F3F3F;
int n, m, s, t;
int mp[N][N];

int djk(int s, int e) {
	static char known[N]; memset(known, 0, sizeof(known));
	// remember the init distance should be a very large number
	static int dis[N]; memset(dis, 0x3F, sizeof(dis));
	
	known[s] = true;
	// init
	for (int i = 1; i <= n; i++) {
		if (mp[s][i]) dis[i] = mp[s][i];
	}
	
	for (int i = 1; i <= n; i++) {
		int minn = INF, mpos;
		// searching for the smaller distance (point)
		for (int k = 1; k <= n; k++) {
			if (!known[k] && dis[k] < minn)
				minn = dis[k], mpos = k;
		}
		
		known[mpos] = true;
		// update dis (do not update known ones)
		for (int k = 1; k <= n; k++) {
			if (mp[mpos][k] != INF) // !! this maybe is for no use, 'cause mp[i][j] is set to INF in main
			if (!known[k]) dis[k] = min(dis[k], dis[mpos] + mp[mpos][k]);
		}
	}
	
	return dis[e];
}

int main() {
	memset(mp, 0x3f, sizeof(mp));
	
	scanf("%d %d %d %d", &n, &m, &s, &t);
	
	int u, v, w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		mp[u][v] = mp[v][u] = w;
	}
	
	printf("%d\n", djk(s, t));
	return 0;
}
