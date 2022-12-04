#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <iostream>

/*
This file is for data structures' templates
*/

// N is the scale of the data, M may for graph
const int N = 1e2, M = 1e5;

class MergeFindSet {
private:
    int grp[N];
public:
    void init(int n) {
        for (int i = 1; i <= n; ++i) grp[i] = i;
    }

    void merge(int x, int y) {
        grp[find(x)] = find(y);
    }

    int find(int x) {
        static int o; o = x;
        while (grp[x] != x) x = grp[x];
        return grp[o] = x;
        /* find can also write as: (but notice that the space of stack!!!)
        if (grp[x] != x) return grp[x] = find(grp[x]);
        else return x;
        */
    }
};

template<typename T>
class MergeFindSetMap {
private:
    std::map<T, T> grp;
public:
    void init(const T &key) {
        grp[key] = key;
    }

    void merge(const T &a, const T &b) {
        grp[find(a)] = find(b);
    }

    const T& find(const T &x) {
        T k = x; // use k to avoid change the value of x
        while (grp[k] != k) k = grp[k];
        return grp[x] = k;
    }
};

class Log2Factory {
private:
    int lg2[N];
public:
    void init(int n) {
        for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
    }

    int operator() (const int &i) {
        return lg2[i];
    }
};

template<typename T>
class STable {
private:

    typedef T(*OP_FUNC)(T, T);
    Log2Factory Log2;
    T f[N][17]; // maybe most of the times k=17 is ok, make sure 2^k greater than N;
    OP_FUNC op;
public:
    void setOp(OP_FUNC fk) {
        op = fk;
    }

    void init(T *a, int n) {
        for (int i = 1; i <= n; ++i)
            f[i][0] = *(++a);

        int t = Log2(n);
        // f[i][k] is the area of [i, i + 2^k - 1]
        // so f[i][k] can equal to the op sum of [i, i^k - 1]
        // let r = i^k - 1
        // => f[r - (1^k) + 1][k] can equal to the op sum of [i][k]
        for (int k = 1; k <= t; ++k) {
            for (int i = 1; i + (1<<k) - 1 <= n; ++i)
                f[i][k] = op(f[i][k-1], f[i + (1<<(k-1))][k-1]);
        }
    }

    const T query(int l, int r) {
        int k = Log2(r - l + 1);
        return op(f[l][k], f[r - (1<<k) + 1][k]);
    }
};

#define lowbit(i) (i & -i)
class BIT {
private:
    int b[N];
public:
    void update(int i, int d) {
        while (i < N)
            b[i] += d, i += lowbit(i);
    }

    int query(int i) {
        int r = 0;
        while (i)
            r += b[i], i -= lowbit(i);
        return r;
    }
};

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

    // 二分图
    bool isBipartile() {
        static int color[N]; memset(color, 0, sizeof(color));
        // TO complete here!!!
        return true;
    }
};

int main() {
    // For Test

    // Test MergeFindSet
    // MergeFindSet need not to test
    printf("Test MergeFindSet OK\n");

    // Test MergeFindSetMap
    static MergeFindSetMap<int> mfsm;
    mfsm.init(2), mfsm.init(5), mfsm.init(7);
    mfsm.merge(2, 5);
    mfsm.merge(5, 7);
    assert(mfsm.find(2) == mfsm.find(7));
    printf("Test MergeFindSetMap OK\n");

    // Test STable
    int (*max)(int, int) = [](int a, int b) {
        return a > b ? a : b;
    };
    static STable<int> st;
    st.setOp(max);

    int a[N] = {0, 5, 4, 2, 1, 3, 7, 6, 4, 9};
    st.init(a, 9);
    assert(st.query(1, 3) == 5);
    assert(st.query(3, 3) == 2);
    assert(st.query(7, 9) == 9);
    assert(st.query(1, 9) == 9);
    printf("Test STable OK\n");

    // Test BIT
    static BIT bit;
    bit.update(2, 1);
    bit.update(3, -1);
    bit.update(9, 10);
    assert(bit.query(3) == 0);
    assert(bit.query(1) == 0);
    assert(bit.query(2) == 1);
    assert(bit.query(9) == 10);
    assert(bit.query(80) == 10);
    printf("Test BIT OK\n");

    // Test Graph
    printf("Test Graph:\n");
    // Test djk
    static Graph g;
    g.n = 4;
    /*
    1 2 2
    2 3 2
    2 4 1
    1 3 5
    3 4 3
    1 4 4
    */
    g.add(1, 2, 2), g.add(2, 3, 2), g.add(2, 4, 1), g.add(1, 3, 5), g.add(3, 4, 3), g.add(1, 4, 4);
    
    static int dis[N]; memset(dis, 0x3F, sizeof(dis));
    g.djk(1, dis);

    static int ans[5] = {0, 0, 2, 4, 3};
    for (int i = 1; i <= 4; ++i) {
        assert(dis[i] == ans[i]);
        printf("%d ", dis[i]);
    } putchar('\n');
    printf("\tTest Graph DJK ok\n");

    memset(dis, 0x3F, sizeof(dis));
    g.spfa(1, dis);
    for (int i = 1; i <= 4; ++i) {
        assert(dis[i] == ans[i]);
        printf("%d ", dis[i]);
    } putchar('\n');
    printf("\tTest Graph SPFA ok\n");
}