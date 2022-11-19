#include <iostream>
#include <unordered_map> 
#include <cstring>
#include <queue>
#include <stack>

using namespace std;

typedef unordered_map<int, bool> hashSet;
const int N = 1e5 + 2, M = 5e5 + 2, INF = 0x7F7F7F7F;
 
struct Edge {
	int next, to, w;
};
 

class Graph {
private:
	int head[N], size;
	Edge edge[M];
public:
	int n, m;
	
	Graph() {
		memset(head, 0, sizeof(head));
		size = 0;
	}
	void add(int u, int v, int w) {
		++size;
		edge[size].next = head[u], head[u] = size;
		edge[size].to = v, edge[size].w = w;
	}
	
	void bellman_ford(int s, int * dis) {
		dis[s] = 0;
		int i = 0; 
		while (++i < m) {
			bool ok = true;
			// 遍历所有的边 
			for (int from = 1; from <= n; from++) {
				if (dis[from] == INF) continue; // 没有被松弛过，没有意义 
				
				for (int t = head[from]; t; t = edge[t].next) {
					int to = edge[t].to;
					if (dis[to] > dis[from] + edge[t].w) {
						dis[to] = dis[from] + edge[t].w;
						ok = false;
					}
				}
			}
			
			if (ok) break;
		}
	} 

	// SFPA 队列，优化	
	// 后来测试，似乎stack更快？ 
	// 优化了个寂寞哦，还不如不优化 
	void bellman_ford_best(int s, int * dis) {
		static int inq[N]; memset(inq, 0, sizeof(inq)); // in que or not
		static int intm[N]; memset(intm, 0, sizeof(intm)); // times relaxed
		// queue<int> que; que.push(s);
		stack<int> que; que.push(s); 
		dis[s] = 0;
		while (que.size()) {
			// int p = que.front(); que.pop();
			int p = que.top(); que.pop();
			inq[p] = false; // mark it not in que
			
			// Negative weight ring exists
			if (++intm[p] == n) break;
			
			// relax all out line
			for (int t = head[p]; t; t = edge[t].next) {
				int to = edge[t].to;
				// judge and relax
				if (dis[to] > dis[p] + edge[t].w) {
					dis[to] = dis[p] + edge[t].w;
					if (!inq[to]) // push in que and mark it in que.
						que.push(to), inq[to] = true;
				}
			}
		}
	}
}; 

static Graph gp;
int main() {
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);
	gp.n = n, gp.m = m;
	
	int u, v, w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		gp.add(u, v, w);
	}
	
	int dis[N];
	memset(dis, 0x7F, sizeof(dis));
	
	// gp.bellman_ford(s, dis);
	gp.bellman_ford_best(s, dis);
	for (int i = 1; i <= n; i++) printf("%d ", (dis[i] == INF ? (1ll << 31) - 1 : dis[i]));
}
