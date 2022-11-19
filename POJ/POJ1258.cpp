#include <iostream>
#include <queue>
#include <stack>
#include <cstring>
#include <string>
#include <climits>
#include <utility>

const int N = 150, INF = 0x3F3F3F3F;

using namespace std;

int mp[N][N], size = 0;
int n;

// s指最开始寻找的点 
int prim(int s) {
	static int inc[N]; memset(inc, 0, sizeof(inc));
	static int dis[N]; memset(dis, INF, sizeof(dis));
	int sum = 0;

	// init
	for (int i = 0; i < n; i++) dis[i] = mp[i][s];
	dis[s] = 0, inc[s] = 1;
		
	for (int i = 1; i < n; i++) {
		// searching for the shortest path
		int mpo, md = INF;
		for (int j = 0; j < n; j++) {
			if (!inc[j] && dis[j] < md) {
				mpo = j, md = dis[j];
			}
		}
		
		if (md == INT_MAX) return -1; // Error in generating
		
		sum += md;
		inc[mpo] = 1;
		// update the shortest path
		for (int j = 0; j < n; j++) {
			if (!inc[j] && dis[j] > mp[mpo][j]) dis[j] = mp[mpo][j];
		}
	}
	
	return sum;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				scanf("%d", mp[i] + j);
		}
		printf("%d\n", prim(0));
	}
	return 0;	
}
