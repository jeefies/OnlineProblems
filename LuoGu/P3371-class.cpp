#include <queue>
#include <utility>
#include <cstring>
#include <iostream>

const int N = 1e5 + 2, M = 5e5 + 2;

// Not a simple Queue, but a ring
template<typename T>
class Queue {
private:
    int head, tail, len, cap;
    T q[N];
public:
    Queue() : head(0), tail(0), len(0), cap(N) {}

    // return false if cannot push  anymore
    bool push(T v) {
        if (++len > N) return false;
        q[tail++ % N] = v;
        return true;
    }

    bool empty() {
        return head == tail;
    }

    int size() {
        return len;
    }

    T pop() {
        --len;
        return q[head++ % N];
    }
};

struct Edge {
    int next, to, w;
};

class Graph {
private:
    int head[N], tot;
    Edge edge[M];
public:
    int n;

    void add(int u, int v) {
        add(u, v, 0);
    }

    void add(int u, int v, int w) {
        edge[++tot] = {head[u], v, w}, head[u] = tot;
    }

    void djk(int s, int * dis) {
        static int vis[N]; memset(vis, 0, sizeof(vis));
        typedef std::pair<int, int> pii;
        // I would like to explain a bit about why I use priority_queue
        // 1. build a heap by my self is complicated, although it's faster without `-O2`
        // 2. However, std::priority_queue is much more flexible and space reduced.
        // 3. NOIP use `-O2` which makes priority_queue faster than self-build heap.
        std::priority_queue<pii, std::vector<pii>, std::greater<pii> > que;

        dis[s] = 0;
        que.push(std::make_pair(0, s));

        while (que.size()) {
            int x = que.top().second; que.pop();
            if (vis[x]) continue;
            vis[x] = true;

            for (int i = head[x]; i; i = edge[i].next) {
                int y = edge[i].to, w = edge[i].w;
                if (!vis[y] && dis[y] > dis[x] + w) {
                    dis[y] = dis[x] + w;
                    que.push(std::make_pair(dis[y], y));
                }
            }
        }
        // DJK finish
    }

    // if false return, means negetive ring exists
    bool spfa(int s, int * dis) {
        static int it[N]; memset(it, 0, sizeof(it));
        static int iq[N]; memset(iq, 0, sizeof(iq));

        Queue<int> q; q.push(s);
        dis[s] = 0, iq[s] = true;

        while (q.size()) {
            int x = q.pop();
            iq[x] = false;

            for (int i = head[x]; i; i = edge[i].next) {
                int y = edge[i].to, w = edge[i].w;
                if (dis[y] > dis[x] + w) {
                    dis[y] = dis[x] + w;
                    if (!iq[y]) {
                        iq[y] = true, q.push(y);
                        if (++it[y] > n) return false;
                    }
                }
            }
        }
        return true;
    }
};



int main() {
    static Graph g;

    int m, s;
    scanf("%d%d%d", &g.n, &m, &s);

    int u, v, w;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        g.add(u, v, w);
    }

    static int dis[N]; memset(dis, 0x7F, sizeof(dis));
    g.djk(s, dis);

	for (int i = 1; i <= g.n; i++) {
		if (dis[i] == 0x7F7F7F7F) printf("%d ", (1ll << 31)-1);
		else printf("%d ", dis[i]);
	}
    return 0;
}