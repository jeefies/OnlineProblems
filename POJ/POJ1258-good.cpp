#include <iostream>
#include <queue>
#include <stack>
#include <cstring>
#include <string>
#include <climits>
#include <utility>

const int N = 150, INF = 0x3F3F3F3F;

using namespace std;

typedef pair<int, int> pii;
int mp[N][N], size = 0;
int n;

// s指最开始寻找的点 
int prim(int s) {
	static int inc[N]; memset(inc, 0, sizeof(inc));
	static int dis[N]; memset(dis, INF, sizeof(dis));
	int sum = 0;

	// init
	priority_queue<pii, vector<pii>, greater<pii> > que;
	que.push(make_pair(0, s));
		
	while (que.size()) {
		// searching for the shortest path
		int md = que.top().first, mpo = que.top().second; que.pop();
		if (inc[mpo]) continue;
		inc[mpo] = 1;
		
		sum += md;
		
		// update the shortest path
		for (int j = 0; j < n; j++) {
			if (!inc[j]) que.push(make_pair(mp[mpo][j], j));
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
