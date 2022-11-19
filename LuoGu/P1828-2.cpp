#include <iostream>
#include <cstring>

using namespace std;

const int P = 800, N = 500, INF = 0x3F3F3F3F;

int mp[P][P], w[N];

int main() {
	memset(mp, 0x3F, sizeof(mp));
	
	int n, p, c;
	scanf("%d %d %d", &n, &p, &c);
	for (int i = 1; i <= n; i++) scanf("%d", w + i);
	
	int a, b, d;
	for (int i = 1; i <= c; i++) {
		scanf("%d %d %d", &a, &b, &d);
		mp[b][a] = mp[a][b] = d;
	}
	
	for (int i = 1; i <= p; i++) mp[i][i] = 0;
	
	// wasted floy0d
	for (int k = 1; k <= p; ++k) {
		for (int i = 1; i <= p; ++i)
			for (int j = 1; j <= p; ++j)
				mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
	}
	
	int mind = INF;
	for (int s = 1; s <= p; ++s) {
		int sum = 0;
		int tmp;
		for (int i = 1; i <= n; ++i) {
			tmp = mp[w[i]][s];
			if (tmp == INF) break;
			sum += tmp; 
		}
		if (tmp != INF) mind = min(mind, sum);
	}
	
	printf("%d", mind);
	return 0;
}
