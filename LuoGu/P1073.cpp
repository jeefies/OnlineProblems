#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;
const int N = 1e5 + 2, M = 5e5 + 2, INF = 0x3F3F3F3F; 

int n, m;
int val[N];

struct Edge {
	int to, next, w;
};

class Graph {
private:
	int head[N], size;
	Edge edge[M];
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
	
	// fucking spfa +1
	void get_most(int i, int * mark) {
		static int in[N]; memset(in, 0, sizeof(in)); // in que or not
		
		queue<int> que; que.push(i);
		mark[i] = val[i];
		
		while (que.size()) {
			int top = que.front(); que.pop();
			in[top] = false;
			
			// relax all relative 
			for (int t = head[top]; t; t = edge[t].next) {
				int to = edge[t].to;
				if (mark[to] < max(mark[top], val[to])) {
					mark[to] = max(mark[top], val[to]);
					if (!in[to]) in[to] = true, que.push(to);
				}
			}
		}
	}
	
	// fucking spfa +1
	void get_least(int i, int * mark) {
		static int in[N]; memset(in, 0, sizeof(in)); // in que or not

		queue<int> que; que.push(i);
		
		while (que.size()) {
			int top = que.front(); que.pop();
			in[top] = false;
			
			// relax all relative 
			for (int t = head[top]; t; t = edge[t].next) {
				int to = edge[t].to;
				if (mark[to] > min(mark[top], val[to])) {
					mark[to] = min(mark[top], val[to]);
					if (!in[to]) in[to] = true, que.push(to);
				}
			}
		}
	}
};

static Graph g, rg;
int main() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		scanf("%d", val + i);
	
	int u, v, w;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		g.add(u, v, w);
		rg.add(v, u, w);
		if (w == 2) g.add(v, u, w), rg.add(u, v, w);
	}
	
	static int minB[N]; 
	memset(minB, 0x3F, sizeof(minB));
	g.get_least(1, minB);
	
	static int maxB[N]; memset(maxB, 0, sizeof(maxB));
	rg.get_most(n, maxB);
	
	// for (int i = 1; i <= n; i++) printf("%d ", maxB[i]); putchar('\n');
	// for (int i = 1; i <= n; i++) printf("%d ", minB[i]); putchar('\n');
	int win = 0;
	for (int i = 1; i <= n; i++) win = max(win, maxB[i] - minB[i]);
	
	printf("%d", win);
}
