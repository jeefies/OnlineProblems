#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

const int N = 1e3 + 2;

struct Edge {
	int to, next, w;
};

class Graph {
private:
	int head[N], size;
	Edge edge[N * 100];
	
	struct P {
		int p, w;
		bool operator < (const P &p) const {
			return w > p.w;
		}
	};
public:
	Graph() {
		memset(head, 0, sizeof(head));
		size = 0;
	}
	
	void add(int u, int v, int w) {
		++size;
		edge[size].next = head[u], head[u] = size;
		edge[size].to = v, edge[size].w = w;
	}
	
	void djk(int s, int * dis) {
		static int vis[N]; memset(vis, 0, sizeof(vis));

		// init		
		dis[s] = 0;

		// init que
		priority_queue<P> que;
		P p = {s, 0};
		que.push(p);
		
		while (!que.empty()) {
			p = que.top(); que.pop();
			int mpos = p.p;
			
			if (vis[mpos]) continue;
			vis[mpos] = true;
			
			for (int t = head[mpos]; t; t = edge[t].next) {
				int to = edge[t].to;
				if (!vis[to] && dis[to] > dis[mpos] + edge[t].w) {
					dis[to] = dis[mpos] + edge[t].w;
					p.w = dis[to], p.p = to; que.push(p);
				}
			}
		}
	}
};

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int u, v, w;
	static Graph a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		a.add(u, v, w);
		b.add(v, u, w);
	}
	
	long long sum = 0;
	static int s[N];
	memset(s, 0x3F, sizeof(s)); a.djk(1, s);
	for (int i = 1; i <= n; i++) sum += s[i];
	memset(s, 0x3F, sizeof(s)); b.djk(1, s);
	for (int i = 1; i <= n; i++) sum += s[i];
	printf("%lld\n", sum);
}