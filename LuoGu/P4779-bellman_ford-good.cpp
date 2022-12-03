#include <iostream>
#include <unordered_map> 
#include <cstring>

using namespace std;

typedef unordered_map<int, bool> hashSet;
const int N = 1e5 + 2, M = 2 * N, INF = 0x7F7F7F7F;
 
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
		size = 0;
	}
	void add(int u, int v, int w) {
		++size;
		edge[size].next = head[u], head[u] = size;
		edge[size].to = v, edge[size].w = w;
	}
	
	void bellman_ford(int s, int * dis) {
		dis[s] = 0;
		while (true) {
			printf("Loop enter!\n");
			bool ok = true;
			// 遍历所有的边 
			for (int from = 1; from <= n; from++) {
				printf("\tfrom %d searching:\n", from); 
				if (dis[from] == INF) continue; // 没有被松弛过，没有意义 
				
				for (int t = head[from]; t; t = edge[t].next) {
					int to = edge[t].to;
					if (dis[to] > dis[from] + edge[to].w) {
						dis[to] = dis[from] + edge[to].w;
						ok = false;
					}
					printf("\t\tupdate (%d -> %d) to %d\n", from, to, dis[to]);
				}
			}
			
			printf("Loop end!\n");
			if (ok) break;
		}
	} 
	
	void bellman_ford_best(int s, int * dis) {
		hashSet changed, newchanged;
		dis[s] = 0;
		changed[s] = true;
		
		while (changed.size()) {
			newchanged.clear();
			
			auto iter = changed.begin(), end = changed.end();
			for (; iter != end; ++iter) {
				int i = (*iter).first;
				for (int t = head[i]; t; t = edge[t].next) {
					int to = edge[t].to;
					if (dis[to] > dis[i] + edge[t].w) {
						dis[to] = dis[i] + edge[t].w;
						newchanged[to] = true;
					}
				}
			}
			
			swap(changed, newchanged);
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
	
	gp.bellman_ford(s, dis);
	for (int i = 1; i <= n; i++) printf("%d ", dis[i]);
}
