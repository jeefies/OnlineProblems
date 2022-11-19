#include <iostream>
#include <cstring>
#include <queue>
#include <climits>

using namespace std;

const int N = 5e5, INF = 0x7F7F7F7F;

int head[N], size = 0;
struct Edge {
	int to, w, next;
} edge[N];

void add(int u, int v, int w) { ++size;
	edge[size].next = head[u], head[u] = size;
	edge[size].to = v, edge[size].w = w;
}

int n;
bool spfa(int s, int * dis) {
	static int inq[N]; // memset(inq, 0, sizeof(inq));
	static int it[N]; // memset(it, 0, sizeof(it));
	
	queue<int> que; que.push(s);
	dis[s] = 0;
	
	while (que.size()) {
		int p = que.front(); que.pop();
		inq[p] = 0;
		
		for (int i = head[p]; i; i = edge[i].next) {
			int to = edge[i].to, w = edge[i].w;
			if (dis[to] > dis[p] + w) {
				dis[to] = dis[p] + w;
				if (!inq[to]) {
					inq[to] = true, que.push(to);
					if (++it[to] > n) return false;
				}
			}
		}
	}
	return true;
}

int main() {
	int ml, md;
	scanf("%d %d %d", &n, &ml, &md);
	
	/*
	!! any i < j <=> s[i] < s[j]
	*/
	int a, b, d;
	/*
	like: 
		|s[a] - s[b]| <= d
	=>	s[b] - s[a] <= d 
	*/
	for (int i = 0; i < ml; i++) {
		scanf("%d %d %d", &a, &b, &d);
		add(a, b, d);
	}
	/*
	dislike:
		|s[a] - s[b]| >= d
	=> 	s[b] - s[a] >= d
	=> s[a] - s[b] <= -d
	*/
	for (int i = 0; i < md; i++) {
		scanf("%d %d %d", &a, &b, &d);
		add(b, a, -d);
	}
	
	static int dis[N]; memset(dis, 0x7F, sizeof(dis));
	if (spfa(1, dis))
		if (dis[n] != INF) printf("%d", dis[n]);
		else printf("-2");
	else printf("-1");
	return 0;
}
