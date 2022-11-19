#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

const int M = 100 + 2, N = 500 + 2, INF = 0x3F3F3F3F;
struct Edge {
	int next, to, w;
};

int head[N], size = 0;
Edge edge[N * 20];

void add(int u, int v, int w) {
	++size;
	edge[size].next = head[u], head[u] = size;
	edge[size].to = v, edge[size].w = w;
}

void spfa(int i, int * dis) {
	static int inq[N]; memset(inq, 0, sizeof(inq)); 
	queue<int> que;
	
	que.push(i); dis[i] = 0;
	while (que.size()) {
		int top = que.front(); que.pop();
		inq[top] = false;
		
		for (int t = head[top]; t; t = edge[t].next) {
			int to = edge[t].to;
			if (dis[to] > dis[top] + edge[t].w) {
				dis[to] = dis[top] + edge[t].w;
				if (!inq[to]) inq[to] = true, que.push(to);
			}
		}
	}
}


int main() {
	// memset(mp, 0x3F, sizeof(mp));
	
	int m, n;
	scanf("%d %d", &m, &n);
	
	static string line;
	static int a[N];
	for (int i = 0; i < m; i++) {
		static char tmp;
		static int k;
		int cnt = 0;
		while (true) {
			scanf("%d", &k);
			a[cnt++] = k;
			if (getchar() != ' ') break;
		}
		
		for (int i = 0; i < cnt; i++) {
			for (int j = i + 1; j < cnt; j++)
				add(a[i], a[j], 1);
		}
	}
	
	static int dis[N]; memset(dis, 0x3F, sizeof(dis));
	spfa(1, dis);
	if (dis[n] == INF) cout << "NO" << endl;
	else cout << dis[n] - 1 << endl;
}
